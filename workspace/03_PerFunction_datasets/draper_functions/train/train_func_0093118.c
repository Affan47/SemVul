csio_mb_fwevt_handler(struct csio_hw *hw, __be64 *cmd)
{
	uint8_t opcode = *(uint8_t *)cmd;
	struct fw_port_cmd *pcmd;
	uint8_t port_id;
	uint32_t link_status;
	uint16_t action;
	uint8_t mod_type;

	if (opcode == FW_PORT_CMD) {
		pcmd = (struct fw_port_cmd *)cmd;
		port_id = FW_PORT_CMD_PORTID_G(
				ntohl(pcmd->op_to_portid));
		action = FW_PORT_CMD_ACTION_G(
				ntohl(pcmd->action_to_len16));
		if (action != FW_PORT_ACTION_GET_PORT_INFO) {
			csio_err(hw, "Unhandled FW_PORT_CMD action: %u\n",
				action);
			return -EINVAL;
		}

		link_status = ntohl(pcmd->u.info.lstatus_to_modtype);
		mod_type = FW_PORT_CMD_MODTYPE_G(link_status);

		hw->pport[port_id].link_status =
			FW_PORT_CMD_LSTATUS_G(link_status);
		hw->pport[port_id].link_speed =
			FW_PORT_CMD_LSPEED_G(link_status);

		csio_info(hw, "Port:%x - LINK %s\n", port_id,
			FW_PORT_CMD_LSTATUS_G(link_status) ? "UP" : "DOWN");

		if (mod_type != hw->pport[port_id].mod_type) {
			hw->pport[port_id].mod_type = mod_type;
			csio_mb_portmod_changed(hw, port_id);
		}
	} else if (opcode == FW_DEBUG_CMD) {
		csio_mb_dump_fw_dbg(hw, cmd);
	} else {
		csio_dbg(hw, "Gen MB can't handle op:0x%x on evtq.\n", opcode);
		return -EINVAL;
	}

	return 0;
}
