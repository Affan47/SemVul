setup_APIC_mce_threshold(int reserved, int new)
{
	if (reserved < 0 && !setup_APIC_eilvt(new, THRESHOLD_APIC_VECTOR,
					      APIC_EILVT_MSG_FIX, 0))
		return new;

	return reserved;
}
