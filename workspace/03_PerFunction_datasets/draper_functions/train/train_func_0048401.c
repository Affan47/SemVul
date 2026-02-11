dbgdev_address_watch_set_registers(
			const struct dbg_address_watch_info *adw_info,
			union TCP_WATCH_ADDR_H_BITS *addrHi,
			union TCP_WATCH_ADDR_L_BITS *addrLo,
			union TCP_WATCH_CNTL_BITS *cntl,
			unsigned int index, unsigned int vmid)
{
	union ULARGE_INTEGER addr;

	BUG_ON(!adw_info || !addrHi || !addrLo || !cntl);

	addr.quad_part = 0;
	addrHi->u32All = 0;
	addrLo->u32All = 0;
	cntl->u32All = 0;

	if (adw_info->watch_mask != NULL)
		cntl->bitfields.mask =
			(uint32_t) (adw_info->watch_mask[index] &
					ADDRESS_WATCH_REG_CNTL_DEFAULT_MASK);
	else
		cntl->bitfields.mask = ADDRESS_WATCH_REG_CNTL_DEFAULT_MASK;

	addr.quad_part = (unsigned long long) adw_info->watch_address[index];

	addrHi->bitfields.addr = addr.u.high_part &
					ADDRESS_WATCH_REG_ADDHIGH_MASK;
	addrLo->bitfields.addr =
			(addr.u.low_part >> ADDRESS_WATCH_REG_ADDLOW_SHIFT);

	cntl->bitfields.mode = adw_info->watch_mode[index];
	cntl->bitfields.vmid = (uint32_t) vmid;

	cntl->u32All |= ADDRESS_WATCH_REG_CNTL_ATC_BIT;

	pr_debug("\t\t%20s %08x\n", "set reg mask :", cntl->bitfields.mask);
	pr_debug("\t\t%20s %08x\n", "set reg add high :",
			addrHi->bitfields.addr);
	pr_debug("\t\t%20s %08x\n", "set reg add low :",
			addrLo->bitfields.addr);
}
