blogic_resultcode(struct blogic_adapter *adapter,
		enum blogic_adapter_status adapter_status,
		enum blogic_tgt_status tgt_status)
{
	int hoststatus;

	switch (adapter_status) {
	case BLOGIC_CMD_CMPLT_NORMAL:
	case BLOGIC_LINK_CMD_CMPLT:
	case BLOGIC_LINK_CMD_CMPLT_FLAG:
		hoststatus = DID_OK;
		break;
	case BLOGIC_SELECT_TIMEOUT:
		hoststatus = DID_TIME_OUT;
		break;
	case BLOGIC_INVALID_OUTBOX_CODE:
	case BLOGIC_INVALID_CMD_CODE:
	case BLOGIC_BAD_CMD_PARAM:
		blogic_warn("BusLogic Driver Protocol Error 0x%02X\n",
				adapter, adapter_status);
	case BLOGIC_DATA_UNDERRUN:
	case BLOGIC_DATA_OVERRUN:
	case BLOGIC_NOEXPECT_BUSFREE:
	case BLOGIC_LINKCCB_BADLUN:
	case BLOGIC_AUTOREQSENSE_FAIL:
	case BLOGIC_TAGQUEUE_REJECT:
	case BLOGIC_BAD_MSG_RCVD:
	case BLOGIC_HW_FAIL:
	case BLOGIC_BAD_RECONNECT:
	case BLOGIC_ABRT_QUEUE:
	case BLOGIC_ADAPTER_SW_ERROR:
	case BLOGIC_HW_TIMEOUT:
	case BLOGIC_PARITY_ERR:
		hoststatus = DID_ERROR;
		break;
	case BLOGIC_INVALID_BUSPHASE:
	case BLOGIC_NORESPONSE_TO_ATN:
	case BLOGIC_HW_RESET:
	case BLOGIC_RST_FROM_OTHERDEV:
	case BLOGIC_HW_BDR:
		hoststatus = DID_RESET;
		break;
	default:
		blogic_warn("Unknown Host Adapter Status 0x%02X\n", adapter,
				adapter_status);
		hoststatus = DID_ERROR;
		break;
	}
	return (hoststatus << 16) | tgt_status;
}
