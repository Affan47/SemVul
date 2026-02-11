do_geeprom(struct cmd_context *ctx)
{
	int geeprom_changed = 0;
	int geeprom_dump_raw = 0;
	u32 geeprom_offset = 0;
	u32 geeprom_length = -1;
	struct cmdline_info cmdline_geeprom[] = {
		{ "offset", CMDL_U32, &geeprom_offset, NULL },
		{ "length", CMDL_U32, &geeprom_length, NULL },
		{ "raw", CMDL_BOOL, &geeprom_dump_raw, NULL },
	};
	int err;
	struct ethtool_drvinfo drvinfo;
	struct ethtool_eeprom *eeprom;

	parse_generic_cmdline(ctx, &geeprom_changed,
			      cmdline_geeprom, ARRAY_SIZE(cmdline_geeprom));

	drvinfo.cmd = ETHTOOL_GDRVINFO;
	err = send_ioctl(ctx, &drvinfo);
	if (err < 0) {
		perror("Cannot get driver information");
		return 74;
	}

	if (geeprom_length == -1)
		geeprom_length = drvinfo.eedump_len;

	if (drvinfo.eedump_len < geeprom_offset + geeprom_length)
		geeprom_length = drvinfo.eedump_len - geeprom_offset;

	eeprom = calloc(1, sizeof(*eeprom)+geeprom_length);
	if (!eeprom) {
		perror("Cannot allocate memory for EEPROM data");
		return 75;
	}
	eeprom->cmd = ETHTOOL_GEEPROM;
	eeprom->len = geeprom_length;
	eeprom->offset = geeprom_offset;
	err = send_ioctl(ctx, eeprom);
	if (err < 0) {
		perror("Cannot get EEPROM data");
		free(eeprom);
		return 74;
	}
	err = dump_eeprom(geeprom_dump_raw, &drvinfo, eeprom);
	free(eeprom);

	return err;
}
