esas2r_send_ae_event(struct esas2r_fw_event_work *fw_event)
{
	struct esas2r_vda_ae *ae = (struct esas2r_vda_ae *)fw_event->data;
	char *type;

	switch (ae->vda_ae.hdr.bytype) {
	case VDAAE_HDR_TYPE_RAID:
		type = "RAID group state change";
		break;

	case VDAAE_HDR_TYPE_LU:
		type = "Mapped destination LU change";
		break;

	case VDAAE_HDR_TYPE_DISK:
		type = "Physical disk inventory change";
		break;

	case VDAAE_HDR_TYPE_RESET:
		type = "Firmware reset";
		break;

	case VDAAE_HDR_TYPE_LOG_INFO:
		type = "Event Log message (INFO level)";
		break;

	case VDAAE_HDR_TYPE_LOG_WARN:
		type = "Event Log message (WARN level)";
		break;

	case VDAAE_HDR_TYPE_LOG_CRIT:
		type = "Event Log message (CRIT level)";
		break;

	case VDAAE_HDR_TYPE_LOG_FAIL:
		type = "Event Log message (FAIL level)";
		break;

	case VDAAE_HDR_TYPE_NVC:
		type = "NVCache change";
		break;

	case VDAAE_HDR_TYPE_TLG_INFO:
		type = "Time stamped log message (INFO level)";
		break;

	case VDAAE_HDR_TYPE_TLG_WARN:
		type = "Time stamped log message (WARN level)";
		break;

	case VDAAE_HDR_TYPE_TLG_CRIT:
		type = "Time stamped log message (CRIT level)";
		break;

	case VDAAE_HDR_TYPE_PWRMGT:
		type = "Power management";
		break;

	case VDAAE_HDR_TYPE_MUTE:
		type = "Mute button pressed";
		break;

	case VDAAE_HDR_TYPE_DEV:
		type = "Device attribute change";
		break;

	default:
		type = "Unknown";
		break;
	}

	esas2r_log(ESAS2R_LOG_WARN,
		   "An async event of type \"%s\" was received from the firmware.  The event contents are:",
		   type);
	esas2r_log_hexdump(ESAS2R_LOG_WARN, &ae->vda_ae,
			   ae->vda_ae.hdr.bylength);

}
