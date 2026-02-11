write_password_to_file(const char *secretfn, const char *password) {
	struct ast_config *conf;
	struct ast_category *cat;
	struct ast_variable *var;
	int res = -1;

	if (!(conf = ast_config_new())) {
		ast_log(LOG_ERROR, "Error creating new config structure\n");
		return res;
	}
	if (!(cat = ast_category_new("general", "", 1))) {
		ast_log(LOG_ERROR, "Error creating new category structure\n");
		ast_config_destroy(conf);
		return res;
	}
	if (!(var = ast_variable_new("password", password, ""))) {
		ast_log(LOG_ERROR, "Error creating new variable structure\n");
		ast_config_destroy(conf);
		ast_category_destroy(cat);
		return res;
	}
	ast_category_append(conf, cat);
	ast_variable_append(cat, var);
	if (!ast_config_text_file_save(secretfn, conf, "app_voicemail")) {
		res = 0;
	} else {
		ast_log(LOG_ERROR, "Error writing voicemail password to %s\n", secretfn);
	}

	ast_config_destroy(conf);
	return res;
}
