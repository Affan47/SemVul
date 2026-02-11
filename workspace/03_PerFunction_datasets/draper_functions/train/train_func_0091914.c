clear_APIC_ibs(void *dummy)
{
	int offset;

	offset = get_ibs_lvt_offset();
	if (offset >= 0)
		setup_APIC_eilvt(offset, 0, APIC_EILVT_MSG_FIX, 1);
}
