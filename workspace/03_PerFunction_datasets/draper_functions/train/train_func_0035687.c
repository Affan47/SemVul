qlcnic_read_memory_test_agent(struct qlcnic_adapter *adapter,
					 struct __mem *mem, __le32 *buffer,
					 int *ret)
{
	u32 addr, data, test;
	int i, reg_read;

	reg_read = mem->size;
	addr = mem->addr;

	if ((addr & 0xf) || (reg_read%16)) {
		dev_info(&adapter->pdev->dev,
			 "Unaligned memory addr:0x%x size:0x%x\n",
			 addr, reg_read);
		*ret = -EINVAL;
		return 0;
	}

	mutex_lock(&adapter->ahw->mem_lock);

	while (reg_read != 0) {
		qlcnic_ind_wr(adapter, QLCNIC_MS_ADDR_LO, addr);
		qlcnic_ind_wr(adapter, QLCNIC_MS_ADDR_HI, 0);
		qlcnic_ind_wr(adapter, QLCNIC_MS_CTRL, QLCNIC_TA_START_ENABLE);

		for (i = 0; i < MAX_CTL_CHECK; i++) {
			test = qlcnic_ind_rd(adapter, QLCNIC_MS_CTRL);
			if (!(test & TA_CTL_BUSY))
				break;
		}
		if (i == MAX_CTL_CHECK) {
			if (printk_ratelimit()) {
				dev_err(&adapter->pdev->dev,
					"failed to read through agent\n");
				*ret = -EIO;
				goto out;
			}
		}
		for (i = 0; i < 4; i++) {
			data = qlcnic_ind_rd(adapter, qlcnic_ms_read_data[i]);
			*buffer++ = cpu_to_le32(data);
		}
		addr += 16;
		reg_read -= 16;
		ret += 16;
	}
out:
	mutex_unlock(&adapter->ahw->mem_lock);
	return mem->size;
}
