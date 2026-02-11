disconnect(struct AdapterCtlBlk *acb)
{
	struct DeviceCtlBlk *dcb = acb->active_dcb;
	struct ScsiReqBlk *srb;

	if (!dcb) {
		dprintkl(KERN_ERR, "disconnect: No such device\n");
		udelay(500);

		acb->last_reset =
		    jiffies + HZ / 2 +
		    HZ * acb->eeprom.delay_time;
		clear_fifo(acb, "disconnectEx");
		DC395x_write16(acb, TRM_S1040_SCSI_CONTROL, DO_HWRESELECT);
		return;
	}
	srb = dcb->active_srb;
	acb->active_dcb = NULL;
	dprintkdbg(DBG_0, "disconnect: (0x%p)\n", srb->cmd);

	srb->scsi_phase = PH_BUS_FREE;
	clear_fifo(acb, "disconnect");
	DC395x_write16(acb, TRM_S1040_SCSI_CONTROL, DO_HWRESELECT);
	if (srb->state & SRB_UNEXPECT_RESEL) {
		dprintkl(KERN_ERR,
			"disconnect: Unexpected reselection <%02i-%i>\n",
			dcb->target_id, dcb->target_lun);
		srb->state = 0;
		waiting_process_next(acb);
	} else if (srb->state & SRB_ABORT_SENT) {
		dcb->flag &= ~ABORT_DEV_;
		acb->last_reset = jiffies + HZ / 2 + 1;
		dprintkl(KERN_ERR, "disconnect: SRB_ABORT_SENT\n");
		doing_srb_done(acb, DID_ABORT, srb->cmd, 1);
		waiting_process_next(acb);
	} else {
		if ((srb->state & (SRB_START_ + SRB_MSGOUT))
		    || !(srb->
			 state & (SRB_DISCONNECT + SRB_COMPLETED))) {


			if (srb->state != SRB_START_
			    && srb->state != SRB_MSGOUT) {
				srb->state = SRB_READY;
				dprintkl(KERN_DEBUG,
					"disconnect: (0x%p) Unexpected\n",
					srb->cmd);
				srb->target_status = SCSI_STAT_SEL_TIMEOUT;
				goto disc1;
			} else {

				dprintkdbg(DBG_KG, "disconnect: (0x%p) "
					"<%02i-%i> SelTO\n", srb->cmd,
					dcb->target_id, dcb->target_lun);
				if (srb->retry_count++ > DC395x_MAX_RETRIES
				    || acb->scan_devices) {
					srb->target_status =
					    SCSI_STAT_SEL_TIMEOUT;
					goto disc1;
				}
				free_tag(dcb, srb);
				srb_going_to_waiting_move(dcb, srb);
				dprintkdbg(DBG_KG,
					"disconnect: (0x%p) Retry\n",
					srb->cmd);
				waiting_set_timer(acb, HZ / 20);
			}
		} else if (srb->state & SRB_DISCONNECT) {
			u8 bval = DC395x_read8(acb, TRM_S1040_SCSI_SIGNAL);


			if (bval & 0x40) {
				dprintkdbg(DBG_0, "disconnect: SCSI bus stat "
					" 0x%02x: ACK set! Other controllers?\n",
					bval);

			} else
				waiting_process_next(acb);
		} else if (srb->state & SRB_COMPLETED) {
		      disc1:


			free_tag(dcb, srb);
			dcb->active_srb = NULL;
			srb->state = SRB_FREE;
			srb_done(acb, dcb, srb);
		}
	}
}
