ahc_linux_queue_cmd_complete(struct ahc_softc *ahc, struct scsi_cmnd *cmd)
{


	{
		u_int new_status;

		switch (ahc_cmd_get_transaction_status(cmd)) {
		case CAM_REQ_INPROG:
		case CAM_REQ_CMP:
		case CAM_SCSI_STATUS_ERROR:
			new_status = DID_OK;
			break;
		case CAM_REQ_ABORTED:
			new_status = DID_ABORT;
			break;
		case CAM_BUSY:
			new_status = DID_BUS_BUSY;
			break;
		case CAM_REQ_INVALID:
		case CAM_PATH_INVALID:
			new_status = DID_BAD_TARGET;
			break;
		case CAM_SEL_TIMEOUT:
			new_status = DID_NO_CONNECT;
			break;
		case CAM_SCSI_BUS_RESET:
		case CAM_BDR_SENT:
			new_status = DID_RESET;
			break;
		case CAM_UNCOR_PARITY:
			new_status = DID_PARITY;
			break;
		case CAM_CMD_TIMEOUT:
			new_status = DID_TIME_OUT;
			break;
		case CAM_UA_ABORT:
		case CAM_REQ_CMP_ERR:
		case CAM_AUTOSENSE_FAIL:
		case CAM_NO_HBA:
		case CAM_DATA_RUN_ERR:
		case CAM_UNEXP_BUSFREE:
		case CAM_SEQUENCE_FAIL:
		case CAM_CCB_LEN_ERR:
		case CAM_PROVIDE_FAIL:
		case CAM_REQ_TERMIO:
		case CAM_UNREC_HBA_ERROR:
		case CAM_REQ_TOO_BIG:
			new_status = DID_ERROR;
			break;
		case CAM_REQUEUE_REQ:
			new_status = DID_REQUEUE;
			break;
		default:

			new_status = DID_ERROR;
			break;
		}

		ahc_cmd_set_transaction_status(cmd, new_status);
	}

	cmd->scsi_done(cmd);
}
