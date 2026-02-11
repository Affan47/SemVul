mpt3sas_base_get_smid_hpr(struct MPT3SAS_ADAPTER *ioc, u8 cb_idx)
{
	unsigned long flags;
	struct request_tracker *request;
	u16 smid;

	spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
	if (list_empty(&ioc->hpr_free_list)) {
		spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);
		return 0;
	}

	request = list_entry(ioc->hpr_free_list.next,
	    struct request_tracker, tracker_list);
	request->cb_idx = cb_idx;
	smid = request->smid;
	list_del(&request->tracker_list);
	spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);
	return smid;
}
