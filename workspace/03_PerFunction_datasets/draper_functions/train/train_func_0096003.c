csio_mb_portmod_changed(struct csio_hw *hw, uint8_t port_id)
{
	static char *mod_str[] = {
		NULL, "LR", "SR", "ER", "TWINAX", "active TWINAX", "LRM"
	};

	struct csio_pport *port = &hw->pport[port_id];

	if (port->mod_type == FW_PORT_MOD_TYPE_NONE)
		csio_info(hw, "Port:%d - port module unplugged\n", port_id);
	else if (port->mod_type < ARRAY_SIZE(mod_str))
		csio_info(hw, "Port:%d - %s port module inserted\n", port_id,
			  mod_str[port->mod_type]);
	else if (port->mod_type == FW_PORT_MOD_TYPE_NOTSUPPORTED)
		csio_info(hw,
			  "Port:%d - unsupported optical port module "
			  "inserted\n", port_id);
	else if (port->mod_type == FW_PORT_MOD_TYPE_UNKNOWN)
		csio_info(hw,
			  "Port:%d - unknown port module inserted, forcing "
			  "TWINAX\n", port_id);
	else if (port->mod_type == FW_PORT_MOD_TYPE_ERROR)
		csio_info(hw, "Port:%d - transceiver module error\n", port_id);
	else
		csio_info(hw, "Port:%d - unknown module type %d inserted\n",
			  port_id, port->mod_type);
}
