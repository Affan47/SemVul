efx_ptp_s27_to_ktime_correction(u32 nic_major, u32 nic_minor,
					       s32 correction)
{

	nic_minor += correction;
	if ((s32)nic_minor < 0) {
		nic_minor += S27_MINOR_MAX;
		nic_major--;
	} else if (nic_minor >= S27_MINOR_MAX) {
		nic_minor -= S27_MINOR_MAX;
		nic_major++;
	}

	return efx_ptp_s27_to_ktime(nic_major, nic_minor);
}
