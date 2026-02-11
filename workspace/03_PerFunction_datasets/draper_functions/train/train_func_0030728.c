hv_kbd_handle_received_packet(struct hv_device *hv_dev,
					  struct vmpacket_descriptor *desc,
					  u32 bytes_recvd,
					  u64 req_id)
{
	struct synth_kbd_msg *msg;
	u32 msg_sz;

	switch (desc->type) {
	case VM_PKT_COMP:
		break;

	case VM_PKT_DATA_INBAND:


		msg_sz = bytes_recvd - (desc->offset8 << 3);
		if (msg_sz <= sizeof(struct synth_kbd_msg_hdr)) {


			dev_err(&hv_dev->device,
				"Illegal packet (type: %d, tid: %llx, size: %d)\n",
				desc->type, req_id, msg_sz);
			break;
		}

		msg = (void *)desc + (desc->offset8 << 3);
		hv_kbd_on_receive(hv_dev, msg, msg_sz);
		break;

	default:
		dev_err(&hv_dev->device,
			"unhandled packet type %d, tid %llx len %d\n",
			desc->type, req_id, bytes_recvd);
		break;
	}
}
