my_device_changestate(struct controlvm_message *inmsg)
{
	struct controlvm_message_packet *cmd = &inmsg->cmd;
	u32 bus_no = cmd->device_change_state.bus_no;
	u32 dev_no = cmd->device_change_state.dev_no;
	struct spar_segment_state state = cmd->device_change_state.state;
	struct visor_device *dev_info;
	int rc = CONTROLVM_RESP_SUCCESS;

	dev_info = visorbus_get_device_by_id(bus_no, dev_no, NULL);
	if (!dev_info) {
		POSTCODE_LINUX_4(DEVICE_CHANGESTATE_FAILURE_PC, dev_no, bus_no,
				 POSTCODE_SEVERITY_ERR);
		rc = -CONTROLVM_RESP_ERROR_DEVICE_INVALID;
	} else if (dev_info->state.created == 0) {
		POSTCODE_LINUX_4(DEVICE_CHANGESTATE_FAILURE_PC, dev_no, bus_no,
				 POSTCODE_SEVERITY_ERR);
		rc = -CONTROLVM_RESP_ERROR_DEVICE_INVALID;
	}
	if ((rc >= CONTROLVM_RESP_SUCCESS) && dev_info)
		device_epilog(dev_info, state,
			      CONTROLVM_DEVICE_CHANGESTATE, &inmsg->hdr, rc,
			      inmsg->hdr.flags.response_expected == 1, 1);
}
