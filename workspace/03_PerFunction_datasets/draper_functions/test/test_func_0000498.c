netxen_md_L1Cache(struct netxen_adapter *adapter,
				struct netxen_minidump_entry_cache
					*cacheEntry, u32 *data_buff)
{
	int i, k, loop_cnt;
	u32 addr, read_addr, read_value, cntrl_addr, tag_reg_addr;
	u32 tag_value, read_cnt;
	u8 cntl_value_w;

	loop_cnt = cacheEntry->op_count;
	read_addr = cacheEntry->read_addr;
	cntrl_addr = cacheEntry->control_addr;
	cntl_value_w = (u32) cacheEntry->write_value;
	tag_reg_addr = cacheEntry->tag_reg_addr;
	tag_value = cacheEntry->init_tag_value;
	read_cnt = cacheEntry->read_addr_cnt;

	for (i = 0; i < loop_cnt; i++) {
		NX_WR_DUMP_REG(tag_reg_addr, adapter->ahw.pci_base0, tag_value);
		NX_WR_DUMP_REG(cntrl_addr, adapter->ahw.pci_base0,
						(u32) cntl_value_w);
		addr = read_addr;
		for (k = 0; k < read_cnt; k++) {
			NX_RD_DUMP_REG(addr,
				adapter->ahw.pci_base0,
						&read_value);
			*data_buff++ = read_value;
			addr += cacheEntry->read_addr_stride;
		}
		tag_value += cacheEntry->tag_value_stride;
	}
	return read_cnt * loop_cnt * sizeof(read_value);
}
