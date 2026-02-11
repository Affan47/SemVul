ipath_set_ib_lstate(struct ipath_devdata *dd, int linkcmd,
				int linitcmd)
{
	u64 mod_wd;
	static const char *what[4] = {
		[0] = "NOP",
		[INFINIPATH_IBCC_LINKCMD_DOWN] = "DOWN",
		[INFINIPATH_IBCC_LINKCMD_ARMED] = "ARMED",
		[INFINIPATH_IBCC_LINKCMD_ACTIVE] = "ACTIVE"
	};

	if (linitcmd == INFINIPATH_IBCC_LINKINITCMD_DISABLE) {


		preempt_disable();
		dd->ipath_flags |= IPATH_IB_LINK_DISABLED;
		preempt_enable();
	} else if (linitcmd) {


		preempt_disable();
		dd->ipath_flags &= ~IPATH_IB_LINK_DISABLED;
		preempt_enable();
	}

	mod_wd = (linkcmd << dd->ibcc_lc_shift) |
		(linitcmd << INFINIPATH_IBCC_LINKINITCMD_SHIFT);
	ipath_cdbg(VERBOSE,
		"Moving unit %u to %s (initcmd=0x%x), current ltstate is %s\n",
		dd->ipath_unit, what[linkcmd], linitcmd,
		ipath_ibcstatus_str[ipath_ib_linktrstate(dd,
			ipath_read_kreg64(dd, dd->ipath_kregs->kr_ibcstatus))]);

	ipath_write_kreg(dd, dd->ipath_kregs->kr_ibcctrl,
			 dd->ipath_ibcctrl | mod_wd);

	(void) ipath_read_kreg64(dd, dd->ipath_kregs->kr_ibcstatus);
}
