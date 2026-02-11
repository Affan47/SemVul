sci_controller_unsolicited_frame(struct isci_host *ihost, u32 ent)
{
	u32 index;
	u32 frame_index;

	struct scu_unsolicited_frame_header *frame_header;
	struct isci_phy *iphy;
	struct isci_remote_device *idev;

	enum sci_status result = SCI_FAILURE;

	frame_index = SCU_GET_FRAME_INDEX(ent);

	frame_header = ihost->uf_control.buffers.array[frame_index].header;
	ihost->uf_control.buffers.array[frame_index].state = UNSOLICITED_FRAME_IN_USE;

	if (SCU_GET_FRAME_ERROR(ent)) {


		sci_controller_release_frame(ihost, frame_index);
		return;
	}

	if (frame_header->is_address_frame) {
		index = SCU_GET_PROTOCOL_ENGINE_INDEX(ent);
		iphy = &ihost->phys[index];
		result = sci_phy_frame_handler(iphy, frame_index);
	} else {

		index = SCU_GET_COMPLETION_INDEX(ent);

		if (index == SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX) {


			index = SCU_GET_PROTOCOL_ENGINE_INDEX(ent);
			iphy = &ihost->phys[index];
			result = sci_phy_frame_handler(iphy, frame_index);
		} else {
			if (index < ihost->remote_node_entries)
				idev = ihost->device_table[index];
			else
				idev = NULL;

			if (idev != NULL)
				result = sci_remote_device_frame_handler(idev, frame_index);
			else
				sci_controller_release_frame(ihost, frame_index);
		}
	}

	if (result != SCI_SUCCESS) {


	}
}
