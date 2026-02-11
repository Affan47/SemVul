il4965_get_hcmd_size(u8 cmd_id, u16 len)
{
	switch (cmd_id) {
	case C_RXON:
		return (u16) sizeof(struct il4965_rxon_cmd);
	default:
		return len;
	}
}
