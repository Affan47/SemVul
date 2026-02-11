qlcnic_83xx_poll_read_list(struct qlcnic_adapter *p_dev,
				       struct qlc_83xx_entry_hdr *p_hdr)
{
	long delay;
	int index, i, j, err;
	struct qlc_83xx_quad_entry *entry;
	struct qlc_83xx_poll *poll;
	unsigned long addr;

	poll = (struct qlc_83xx_poll *)((char *)p_hdr +
					sizeof(struct qlc_83xx_entry_hdr));

	entry = (struct qlc_83xx_quad_entry *)((char *)poll +
					       sizeof(struct qlc_83xx_poll));
	delay = (long)p_hdr->delay;

	for (i = 0; i < p_hdr->count; i++, entry++) {
		qlcnic_83xx_wrt_reg_indirect(p_dev, entry->ar_addr,
					     entry->ar_value);
		if (delay) {
			if (!qlcnic_83xx_poll_reg(p_dev, entry->ar_addr, delay,
						  poll->mask, poll->status)){
				index = p_dev->ahw->reset.array_index;
				addr = entry->dr_addr;
				j = QLCRD32(p_dev, addr, &err);
				if (err == -EIO)
					return;

				p_dev->ahw->reset.array[index++] = j;

				if (index == QLC_83XX_MAX_RESET_SEQ_ENTRIES)
					p_dev->ahw->reset.array_index = 1;
			}
		}
	}
}
