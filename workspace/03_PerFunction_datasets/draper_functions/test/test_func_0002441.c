ay_is_conversation_auto(Conversation *cr)
{
	FILE *fp;
	char buff[4096];
	snprintf(buff, 4095, "%schatroom_autoconnect", config_dir);
	if (!cr->local_user || !cr->name)
		return FALSE;

	eb_debug(DBG_CORE, "buff %s\n", buff);

	if (!(fp = fopen(buff, "r"))) {
		eb_debug(DBG_CORE, "Could not open file %s\n", buff);
		return FALSE;
	}

	while (fgets(buff, sizeof(buff), fp)) {
		char **tokens = ay_strsplit(buff, "\t", -1);
		if (!strcmp(tokens[0],
			    get_service_name(cr->local_user->service_id))
		    && !strcmp(tokens[1], cr->local_user->handle)
		    && !strcmp(tokens[2], cr->name)
		    && atoi(tokens[3]) == cr->is_public) {
			fclose(fp);
			ay_strfreev(tokens);
			return TRUE;
		}
		ay_strfreev(tokens);
	}
	if (fp)
		fclose(fp);

	return FALSE;
}
