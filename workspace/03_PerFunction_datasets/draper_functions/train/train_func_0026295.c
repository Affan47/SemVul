fnic_fcpio_cmpl_handler(struct vnic_dev *vdev,
				   unsigned int cq_index,
				   struct fcpio_fw_req *desc)
{
	struct fnic *fnic = vnic_dev_priv(vdev);

	switch (desc->hdr.type) {
	case FCPIO_ICMND_CMPL:
	case FCPIO_ITMF_CMPL:
	case FCPIO_FLOGI_REG_CMPL:
	case FCPIO_FLOGI_FIP_REG_CMPL:
	case FCPIO_RESET_CMPL:
		atomic64_dec(&fnic->fnic_stats.fw_stats.active_fw_reqs);
		break;
	default:
		break;
	}

	switch (desc->hdr.type) {
	case FCPIO_ACK:
		fnic_fcpio_ack_handler(fnic, cq_index, desc);
		break;

	case FCPIO_ICMND_CMPL:
		fnic_fcpio_icmnd_cmpl_handler(fnic, desc);
		break;

	case FCPIO_ITMF_CMPL:
		fnic_fcpio_itmf_cmpl_handler(fnic, desc);
		break;

	case FCPIO_FLOGI_REG_CMPL:
	case FCPIO_FLOGI_FIP_REG_CMPL:
		fnic_fcpio_flogi_reg_cmpl_handler(fnic, desc);
		break;

	case FCPIO_RESET_CMPL:
		fnic_fcpio_fw_reset_cmpl_handler(fnic, desc);
		break;

	default:
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			      "firmware completion type %d\n",
			      desc->hdr.type);
		break;
	}

	return 0;
}
