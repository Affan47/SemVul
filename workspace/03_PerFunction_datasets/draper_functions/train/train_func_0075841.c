msb_read_regs(struct msb_data *msb, int offset, int len)
{
	struct memstick_request *req = &msb->card->current_mrq;

	if (msb->reg_addr.r_offset != offset ||
	    msb->reg_addr.r_length != len || !msb->addr_valid) {

		msb->reg_addr.r_offset = offset;
		msb->reg_addr.r_length = len;
		msb->addr_valid = true;

		memstick_init_req(req, MS_TPC_SET_RW_REG_ADRS,
			&msb->reg_addr, sizeof(msb->reg_addr));
		return 0;
	}

	memstick_init_req(req, MS_TPC_READ_REG, NULL, len);
	return 1;
}
