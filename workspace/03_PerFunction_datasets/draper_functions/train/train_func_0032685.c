i8k_get_fn_status(void)
{
	struct smm_regs regs = { .eax = I8K_SMM_FN_STATUS, };
	int rc;

	rc = i8k_smm(&regs);
	if (rc < 0)
		return rc;

	switch ((regs.eax >> I8K_FN_SHIFT) & I8K_FN_MASK) {
	case I8K_FN_UP:
		return I8K_VOL_UP;
	case I8K_FN_DOWN:
		return I8K_VOL_DOWN;
	case I8K_FN_MUTE:
		return I8K_VOL_MUTE;
	default:
		return 0;
	}
}
