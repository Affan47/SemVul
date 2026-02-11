read_config(CHAR16 *filename)
{
	EFI_STATUS status;
	INTN ret;

	if (filename == NULL) return EFI_INVALID_PARAMETER;

	VERB_PRT(3, Print(L"trying config file %s\n", filename));

	StrCpy(global_config.config_file, filename);

	status = fops_open(filename, &config_fd);
	if (EFI_ERROR(status)) {
                VERB_PRT(3, Print(L"cannot open config file %s\n", filename));
                return status;
	}


	line_num = 1;

	ret = config_parse();

	fops_close(config_fd);

	DBG_PRT((L"done parsing config file\n"));

	if (ret != 0) return EFI_INVALID_PARAMETER;

	update_elilo_opt();

	return EFI_SUCCESS;
}
