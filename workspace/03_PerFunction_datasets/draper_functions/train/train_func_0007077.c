LogicalConfirmReceivedLocation(XLogRecPtr lsn)
{
	Assert(lsn != InvalidXLogRecPtr);


	if (MyReplicationSlot->candidate_xmin_lsn != InvalidXLogRecPtr ||
		MyReplicationSlot->candidate_restart_valid != InvalidXLogRecPtr)
	{
		bool		updated_xmin = false;
		bool		updated_restart = false;


		volatile ReplicationSlot *slot = MyReplicationSlot;

		SpinLockAcquire(&slot->mutex);

		slot->data.confirmed_flush = lsn;


		if (slot->candidate_xmin_lsn != InvalidXLogRecPtr &&
			slot->candidate_xmin_lsn <= lsn)
		{


			if (TransactionIdIsValid(slot->candidate_catalog_xmin) &&
				slot->data.catalog_xmin != slot->candidate_catalog_xmin)
			{
				slot->data.catalog_xmin = slot->candidate_catalog_xmin;
				slot->candidate_catalog_xmin = InvalidTransactionId;
				slot->candidate_xmin_lsn = InvalidXLogRecPtr;
				updated_xmin = true;
			}
		}

		if (slot->candidate_restart_valid != InvalidXLogRecPtr &&
			slot->candidate_restart_valid <= lsn)
		{
			Assert(slot->candidate_restart_lsn != InvalidXLogRecPtr);

			slot->data.restart_lsn = slot->candidate_restart_lsn;
			slot->candidate_restart_lsn = InvalidXLogRecPtr;
			slot->candidate_restart_valid = InvalidXLogRecPtr;
			updated_restart = true;
		}

		SpinLockRelease(&slot->mutex);


		if (updated_xmin || updated_restart)
		{
			ReplicationSlotMarkDirty();
			ReplicationSlotSave();
			elog(DEBUG1, "updated xmin: %u restart: %u", updated_xmin, updated_restart);
		}


		if (updated_xmin)
		{
			SpinLockAcquire(&slot->mutex);
			slot->effective_catalog_xmin = slot->data.catalog_xmin;
			SpinLockRelease(&slot->mutex);

			ReplicationSlotsComputeRequiredXmin(false);
			ReplicationSlotsComputeRequiredLSN();
		}
	}
	else
	{
		volatile ReplicationSlot *slot = MyReplicationSlot;

		SpinLockAcquire(&slot->mutex);
		slot->data.confirmed_flush = lsn;
		SpinLockRelease(&slot->mutex);
	}
}
