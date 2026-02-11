mce_gather_info(struct mce *m, struct pt_regs *regs)
{
	mce_setup(m);

	m->mcgstatus = mce_rdmsrl(MSR_IA32_MCG_STATUS);
	if (regs) {


		if (m->mcgstatus & (MCG_STATUS_RIPV|MCG_STATUS_EIPV)) {
			m->ip = regs->ip;
			m->cs = regs->cs;


			if (v8086_mode(regs))
				m->cs |= 3;
		}

		if (mca_cfg.rip_msr)
			m->ip = mce_rdmsrl(mca_cfg.rip_msr);
	}
}
