parse_cfg_file(struct imx_header *imxhdr, char *name)
{
	FILE *fd = NULL;
	char *line = NULL;
	char *token, *saveptr1, *saveptr2;
	int lineno = 0;
	int fld;
	size_t len;
	int dcd_len = 0;
	int32_t cmd;

	fd = fopen(name, "r");
	if (fd == 0) {
		fprintf(stderr, "Error: %s - Can't open DCD file\n", name);
		exit(EXIT_FAILURE);
	}


	while ((getline(&line, &len, fd)) > 0) {
		lineno++;

		token = strtok_r(line, "\r\n", &saveptr1);
		if (token == NULL)
			continue;


		for (fld = CFG_COMMAND, cmd = CMD_INVALID,
				line = token; ; line = NULL, fld++) {
			token = strtok_r(line, " \t", &saveptr2);
			if (token == NULL)
				break;


			if (token[0] == '#')
				break;

			parse_cfg_fld(imxhdr, &cmd, token, name,
					lineno, fld, &dcd_len);
		}

	}

	(*set_dcd_rst)(imxhdr, dcd_len, name, lineno);
	fclose(fd);


	if (imximage_ivt_offset == FLASH_OFFSET_UNDEFINED) {
		fprintf(stderr, "Error: No BOOT_FROM tag in %s\n", name);
		exit(EXIT_FAILURE);
	}
	return dcd_len;
}
