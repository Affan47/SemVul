usb_handle_packet_usb_token(
	void *_cpssp,
	int pid,
	int addr,
	int endp
)
{
	struct cpssp * cpssp = (struct cpssp *) _cpssp;

	if (cpssp->state < STATE_DEFAULT) {

		return;
	}


	if (pid != USB_PID_SETUP
	    && pid != USB_PID_IN
	    && pid != USB_PID_OUT) {
		faum_log(FAUM_LOG_ERROR, U2S_LOG_TYPE, U2S_LOG_NAME,
				"unknown PID %02X\n", pid);
		return;
	}


	cpssp->last_token.pid = pid;
	cpssp->last_token.addr = addr;
	cpssp->last_token.endp = endp;

#if U2S_DEBUGMASK & U2S_DEBUG_DUMP_PACKETS
	faum_log(FAUM_LOG_DEBUG, U2S_LOG_TYPE, U2S_LOG_NAME,
			"received %s token to %02d:%02d%s\n",
			cim_usb_debug_pid2str(pid), addr, endp,
			cpssp->addr == addr ? " (this is me!)" : "");
#endif

#if U2S_DEBUGMASK & U2S_DEBUG_STATISTICS
	cpssp->statistics.token_count_total++;
#endif


	if (cpssp->addr != addr) {
		return;
	}

#if U2S_DEBUGMASK & U2S_DEBUG_STATISTICS
	cpssp->statistics.token_count++;

	switch (endp) {
	case 0: cpssp->statistics.token_count_ctrl++; break;
	case USB_ENDPT_NR_INTERRUPT_IN: cpssp->statistics.token_count_int_in++; break;
	case USB_ENDPT_NR_BULK_OUT: cpssp->statistics.token_count_bulk_out++; break;
	case USB_ENDPT_NR_BULK_IN: cpssp->statistics.token_count_bulk_in++; break;
	}
#endif

	if (pid == USB_PID_IN) {
		if (endp == 0) {
			usb_handle_packet_usb_token_in_control(cpssp);
			return;
		}

		if (cpssp->state != STATE_CONFIGURED) {


			return;
		}

		switch (endp) {
		case USB_ENDPT_NR_INTERRUPT_IN:
			usb_handle_packet_usb_token_in_interrupt_in(cpssp);
			break;
		case USB_ENDPT_NR_BULK_IN:
			usb_handle_packet_usb_token_in_bulk_in(cpssp);
			break;
		case USB_ENDPT_NR_BULK_OUT:
#if U2S_DEBUGMASK & U2S_DEBUG_DUMP_PACKETS
			faum_log(FAUM_LOG_DEBUG, U2S_LOG_TYPE, U2S_LOG_NAME,
					"IN token cannot go into an OUT endpoint\n");
#endif

			cpssp->control.stalled = 1;
			usb_send_handshake(cpssp, USB_PID_STALL);
			break;
		default:
#if U2S_DEBUGMASK & U2S_DEBUG_DUMP_PACKETS
			faum_log(FAUM_LOG_DEBUG, U2S_LOG_TYPE, U2S_LOG_NAME,
					"IN token for unknown endpoint\n");
#endif
			cpssp->control.stalled = 1;
			usb_send_handshake(cpssp, USB_PID_STALL);
		}
	} else if (pid == USB_PID_SETUP
		   && endp == 0) {

		cpssp->control_information.stage = STAGE_SETUP;
		cpssp->control.data_toggle = USB_PID_DATA0;
	} else if (pid == USB_PID_OUT
		   && endp == 0
		   && cpssp->control_information.stage == STAGE_DATA
		   && (cpssp->control_information.request.bmRequestType
		       & USB_DEV_REQ_DEVICE_TO_HOST)) {

		cpssp->control_information.stage = STAGE_STATUS;
		cpssp->control.data_toggle = USB_PID_DATA1;
	}
}
