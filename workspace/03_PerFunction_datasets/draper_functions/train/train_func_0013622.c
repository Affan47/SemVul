ay_remove_auto_conversation(eb_local_account *ela, const char *name,
				 int public)
{
	FILE *fp, *tmp;
	char buffin[4095], bufftmp[4095], buff[4095];
	snprintf(bufftmp, 4095, "%schatroom_autoconnect.tmp", config_dir);
	snprintf(buffin, 4095, "%schatroom_autoconnect", config_dir);
	if (!ela || !name)
		return;

	eb_debug(DBG_CORE, "buff %s\n", buffin);
	fp = fopen(buffin, "r");
	tmp = fopen(bufftmp, "w");

	if (!tmp) {
		if (fp)
			fclose(fp);
		return;
	}

	while (fp && fgets(buff, sizeof(buff), fp)) {
		char **tokens = ay_strsplit(buff, "\t", -1);
		if (strcmp(tokens[0], get_service_name(ela->service_id))
		    || strcmp(tokens[1], ela->handle)
		    || strcmp(tokens[2], name)
		    || atoi(tokens[3]) != public) {
			fprintf(tmp, "%s", buff);
		}
	}

	fclose(tmp);

	if (fp) {
		fclose(fp);
		unlink(buffin);
	}
	rename(bufftmp, buffin);
}
