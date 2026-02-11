realtime_directory(char *context)
{
	struct ast_config *cfg;
	struct ast_config *rtdata;
	struct ast_category *cat;
	struct ast_variable *var;
	char *mailbox;
	const char *fullname;
	const char *hidefromdir, *searchcontexts = NULL;
	char tmp[100];
	struct ast_flags config_flags = { 0 };


	cfg = ast_config_load(VOICEMAIL_CONFIG, config_flags);

	if (!cfg) {

		ast_log(LOG_WARNING, "Loading config failed.\n");
		return NULL;
	} else if (cfg == CONFIG_STATUS_FILEINVALID) {
		ast_log(LOG_ERROR, "Config file %s is in an invalid format.  Aborting.\n", VOICEMAIL_CONFIG);
		return NULL;
	}


	if (ast_strlen_zero(context) && (searchcontexts = ast_variable_retrieve(cfg, "general", "searchcontexts"))) {
		if (ast_true(searchcontexts)) {
			rtdata = ast_load_realtime_multientry("voicemail", "mailbox LIKE", "%", SENTINEL);
			context = NULL;
		} else {
			rtdata = ast_load_realtime_multientry("voicemail", "mailbox LIKE", "%", "context", "default", SENTINEL);
			context = "default";
		}
	} else {
		rtdata = ast_load_realtime_multientry("voicemail", "mailbox LIKE", "%", "context", context, SENTINEL);
	}


	if (!rtdata) {
		return cfg;
	}

	mailbox = NULL;
	while ( (mailbox = ast_category_browse(rtdata, mailbox)) ) {
		const char *ctx = ast_variable_retrieve(rtdata, mailbox, "context");

		fullname = ast_variable_retrieve(rtdata, mailbox, "fullname");
		hidefromdir = ast_variable_retrieve(rtdata, mailbox, "hidefromdir");
		if (ast_true(hidefromdir)) {

			continue;
		}
		snprintf(tmp, sizeof(tmp), "no-password,%s", S_OR(fullname, ""));


		if (!(cat = ast_category_get(cfg, ctx))) {
			if (!(cat = ast_category_new(ctx, "", 99999))) {
				ast_log(LOG_WARNING, "Out of memory\n");
				ast_config_destroy(cfg);
				if (rtdata) {
					ast_config_destroy(rtdata);
				}
				return NULL;
			}
			ast_category_append(cfg, cat);
		}

		if ((var = ast_variable_new(mailbox, tmp, ""))) {
			ast_variable_append(cat, var);
		} else {
			ast_log(LOG_WARNING, "Out of memory adding mailbox '%s'\n", mailbox);
		}
	}
	ast_config_destroy(rtdata);

	return cfg;
}
