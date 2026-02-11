controlvm_respond_physdev_changestate(
		struct controlvm_message_header *msg_hdr, int response,
		struct spar_segment_state state)
{
	struct controlvm_message outmsg;

	controlvm_init_response(&outmsg, msg_hdr, response);
	outmsg.cmd.device_change_state.state = state;
	outmsg.cmd.device_change_state.flags.phys_device = 1;
	if (!visorchannel_signalinsert(controlvm_channel,
				       CONTROLVM_QUEUE_REQUEST, &outmsg)) {
		return;
	}
}
