parse_cfg_fld(struct ubl_header *ublhdr, int32_t *cmd,
		char *token, char *name, int lineno, int fld, int *dcd_len)
{

	switch (fld) {
	case CFG_COMMAND:
		*cmd = get_table_entry_id(ublimage_cmds,
			"ublimage commands", token);
		if (*cmd < 0) {
			fprintf(stderr, "Error: %s[%d] - Invalid command"
			"(%s)\n", name, lineno, token);
			exit(EXIT_FAILURE);
		}
		break;
	case CFG_REG_VALUE:
		parse_cfg_cmd(ublhdr, *cmd, token, name, lineno, fld, *dcd_len);
		break;
	default:
		break;
	}
}
