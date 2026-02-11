be_cmd_notify_wait(struct be_adapter *adapter,
			      struct be_mcc_wrb *wrb)
{
	struct be_mcc_wrb *dest_wrb;
	int status;

	status = be_cmd_lock(adapter);
	if (status)
		return status;

	dest_wrb = be_cmd_copy(adapter, wrb);
	if (!dest_wrb) {
		status = -EBUSY;
		goto unlock;
	}

	if (use_mcc(adapter))
		status = be_mcc_notify_wait(adapter);
	else
		status = be_mbox_notify_wait(adapter);

	if (!status)
		memcpy(wrb, dest_wrb, sizeof(*wrb));

unlock:
	be_cmd_unlock(adapter);
	return status;
}
