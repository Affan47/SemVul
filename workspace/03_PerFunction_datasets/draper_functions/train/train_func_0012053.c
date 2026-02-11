amd_deferred_error_interrupt(void)
{
	u64 status;
	unsigned int bank;

	for (bank = 0; bank < mca_cfg.banks; ++bank) {
		rdmsrl(MSR_IA32_MCx_STATUS(bank), status);

		if (!(status & MCI_STATUS_VAL) ||
		    !(status & MCI_STATUS_DEFERRED))
			continue;

		__log_error(bank, false, 0);
		break;
	}
}
