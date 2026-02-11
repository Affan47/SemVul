efi_thunk_get_time(efi_time_t *tm, efi_time_cap_t *tc)
{
	efi_status_t status;
	u32 phys_tm, phys_tc;

	spin_lock(&rtc_lock);

	phys_tm = virt_to_phys(tm);
	phys_tc = virt_to_phys(tc);

	status = efi_thunk(get_time, phys_tm, phys_tc);

	spin_unlock(&rtc_lock);

	return status;
}
