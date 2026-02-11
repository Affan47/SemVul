controlvm_respond(struct controlvm_message_header *msg_hdr, int response)
{
	struct controlvm_message outmsg;

	controlvm_init_response(&outmsg, msg_hdr, response);
	if (outmsg.hdr.flags.test_message == 1)
		return;

	if (!visorchannel_signalinsert(controlvm_channel,
				       CONTROLVM_QUEUE_REQUEST, &outmsg)) {
		return;
	}
}
