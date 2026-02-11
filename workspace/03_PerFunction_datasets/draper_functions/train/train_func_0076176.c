device_epilog(struct visor_device *dev_info,
	      struct spar_segment_state state, u32 cmd,
	      struct controlvm_message_header *msg_hdr, int response,
	      bool need_response, bool for_visorbus)
{
	struct visorchipset_busdev_notifiers *notifiers;
	bool notified = false;
	struct controlvm_message_header *pmsg_hdr = NULL;

	notifiers = &busdev_notifiers;

	if (!dev_info) {


		pmsg_hdr = msg_hdr;
		goto away;
	}

	if (dev_info->pending_msg_hdr) {

		response = -CONTROLVM_RESP_ERROR_MESSAGE_ID_INVALID_FOR_CLIENT;
		pmsg_hdr = dev_info->pending_msg_hdr;
		goto away;
	}

	if (need_response) {
		pmsg_hdr = kzalloc(sizeof(*pmsg_hdr), GFP_KERNEL);
		if (!pmsg_hdr) {
			response = -CONTROLVM_RESP_ERROR_KMALLOC_FAILED;
			goto away;
		}

		memcpy(pmsg_hdr, msg_hdr,
		       sizeof(struct controlvm_message_header));
		dev_info->pending_msg_hdr = pmsg_hdr;
	}

	down(&notifier_lock);
	if (response >= 0) {
		switch (cmd) {
		case CONTROLVM_DEVICE_CREATE:
			if (notifiers->device_create) {
				(*notifiers->device_create) (dev_info);
				notified = true;
			}
			break;
		case CONTROLVM_DEVICE_CHANGESTATE:

			if (state.alive == segment_state_running.alive &&
			    state.operating ==
				segment_state_running.operating) {
				if (notifiers->device_resume) {
					(*notifiers->device_resume) (dev_info);
					notified = true;
				}
			}

			else if (state.alive == segment_state_standby.alive &&
				 state.operating ==
				 segment_state_standby.operating) {


				if (notifiers->device_pause) {
					(*notifiers->device_pause) (dev_info);
					notified = true;
				}
			}
			break;
		case CONTROLVM_DEVICE_DESTROY:
			if (notifiers->device_destroy) {
				(*notifiers->device_destroy) (dev_info);
				notified = true;
			}
			break;
		}
	}
away:
	if (notified)


		;
	else


		device_responder(cmd, pmsg_hdr, response);
	up(&notifier_lock);
}
