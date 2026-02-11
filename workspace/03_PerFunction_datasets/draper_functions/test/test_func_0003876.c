sci_remote_device_frame_handler(struct isci_remote_device *idev,
						     u32 frame_index)
{
	struct sci_base_state_machine *sm = &idev->sm;
	enum sci_remote_device_states state = sm->current_state_id;
	struct isci_host *ihost = idev->owning_port->owning_controller;
	enum sci_status status;

	switch (state) {
	case SCI_DEV_INITIAL:
	case SCI_DEV_STOPPED:
	case SCI_DEV_STARTING:
	case SCI_STP_DEV_IDLE:
	case SCI_SMP_DEV_IDLE:
	case SCI_DEV_FINAL:
	default:
		dev_warn(scirdev_to_dev(idev), "%s: in wrong state: %s\n",
			 __func__, dev_state_name(state));

		sci_controller_release_frame(ihost, frame_index);
		return SCI_FAILURE_INVALID_STATE;
	case SCI_DEV_READY:
	case SCI_STP_DEV_NCQ_ERROR:
	case SCI_STP_DEV_AWAIT_RESET:
	case SCI_DEV_STOPPING:
	case SCI_DEV_FAILED:
	case SCI_DEV_RESETTING: {
		struct isci_request *ireq;
		struct ssp_frame_hdr hdr;
		void *frame_header;
		ssize_t word_cnt;

		status = sci_unsolicited_frame_control_get_header(&ihost->uf_control,
								       frame_index,
								       &frame_header);
		if (status != SCI_SUCCESS)
			return status;

		word_cnt = sizeof(hdr) / sizeof(u32);
		sci_swab32_cpy(&hdr, frame_header, word_cnt);

		ireq = sci_request_by_tag(ihost, be16_to_cpu(hdr.tag));
		if (ireq && ireq->target_device == idev) {

			status = sci_io_request_frame_handler(ireq, frame_index);
		} else {


			sci_controller_release_frame(ihost, frame_index);
		}
		break;
	}
	case SCI_STP_DEV_NCQ: {
		struct dev_to_host_fis *hdr;

		status = sci_unsolicited_frame_control_get_header(&ihost->uf_control,
								       frame_index,
								       (void **)&hdr);
		if (status != SCI_SUCCESS)
			return status;

		if (hdr->fis_type == FIS_SETDEVBITS &&
		    (hdr->status & ATA_ERR)) {
			idev->not_ready_reason = SCIC_REMOTE_DEVICE_NOT_READY_SATA_SDB_ERROR_FIS_RECEIVED;


			sci_change_state(sm, SCI_STP_DEV_NCQ_ERROR);
		} else if (hdr->fis_type == FIS_REGD2H &&
			   (hdr->status & ATA_ERR)) {


			idev->not_ready_reason = SCIC_REMOTE_DEVICE_NOT_READY_SATA_SDB_ERROR_FIS_RECEIVED;
			sci_change_state(&idev->sm, SCI_STP_DEV_NCQ_ERROR);
		} else
			status = SCI_FAILURE;

		sci_controller_release_frame(ihost, frame_index);
		break;
	}
	case SCI_STP_DEV_CMD:
	case SCI_SMP_DEV_CMD:


		status = sci_io_request_frame_handler(idev->working_request, frame_index);
		break;
	}

	return status;
}
