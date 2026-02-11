scsi_debug_lbp(void)
{
	return ((0 == scsi_debug_fake_rw) &&
		(scsi_debug_lbpu | scsi_debug_lbpws | scsi_debug_lbpws10));
}
