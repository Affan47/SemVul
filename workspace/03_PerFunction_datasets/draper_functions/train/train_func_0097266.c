mts_transfer_done( struct urb *transfer )
{
	MTS_INT_INIT();

	context->srb->result &= MTS_SCSI_ERR_MASK;
	context->srb->result |= (unsigned)(*context->scsi_status)<<1;

	mts_transfer_cleanup(transfer);
}
