_base_get_cb_idx(struct MPT3SAS_ADAPTER *ioc, u16 smid)
{
	int i;
	u8 cb_idx;

	if (smid < ioc->hi_priority_smid) {
		i = smid - 1;
		cb_idx = ioc->scsi_lookup[i].cb_idx;
	} else if (smid < ioc->internal_smid) {
		i = smid - ioc->hi_priority_smid;
		cb_idx = ioc->hpr_lookup[i].cb_idx;
	} else if (smid <= ioc->hba_queue_depth) {
		i = smid - ioc->internal_smid;
		cb_idx = ioc->internal_lookup[i].cb_idx;
	} else
		cb_idx = 0xFF;
	return cb_idx;
}
