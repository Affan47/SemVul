fnic_fcpio_flogi_reg_cmpl_handler(struct fnic *fnic,
					     struct fcpio_fw_req *desc)
{
	u8 type;
	u8 hdr_status;
	struct fcpio_tag tag;
	int ret = 0;
	unsigned long flags;

	fcpio_header_dec(&desc->hdr, &type, &hdr_status, &tag);


	spin_lock_irqsave(&fnic->fnic_lock, flags);

	if (fnic->state == FNIC_IN_ETH_TRANS_FC_MODE) {


		if (!hdr_status) {
			FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
				      "flog reg succeeded\n");
			fnic->state = FNIC_IN_FC_MODE;
		} else {
			FNIC_SCSI_DBG(KERN_DEBUG,
				      fnic->lport->host,
				      "fnic flogi reg :failed %s\n",
				      fnic_fcpio_status_to_str(hdr_status));
			fnic->state = FNIC_IN_ETH_MODE;
			ret = -1;
		}
	} else {
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			      "Unexpected fnic state %s while"
			      " processing flogi reg completion\n",
			      fnic_state_to_str(fnic->state));
		ret = -1;
	}

	if (!ret) {
		if (fnic->stop_rx_link_events) {
			spin_unlock_irqrestore(&fnic->fnic_lock, flags);
			goto reg_cmpl_handler_end;
		}
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);

		fnic_flush_tx(fnic);
		queue_work(fnic_event_queue, &fnic->frame_work);
	} else {
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
	}

reg_cmpl_handler_end:
	return ret;
}
