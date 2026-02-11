cfgDump(const char *file, cfgStruct cfg[], cfgFileType type, int max_section)
{
	FILE *fp;
	int retcode;

	fp = fopen(file, "w");
	if (fp == NULL) {
		cfgFatal(CFG_CREATE_FAIL, file, 0, NULL);
		return (-1);
	}

	switch (type) {
	case CFG_SIMPLE:
		retcode = dump_simple(fp, cfg, type);
		break;
	case CFG_INI:
		retcode = dump_ini(fp, cfg, type, max_section);
		break;
	default:
		fclose(fp);
		cfgFatal(CFG_INTERNAL_ERROR, file, 0, NULL);
		return (-1);
	}

	fclose(fp);
	return (retcode);
}
