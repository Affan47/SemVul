toplevel_update_title_bar(toplevel_t * top)
{
	char *log_path = seaudit_get_log_path(top->s);
	apol_policy_path_t *policy_path = seaudit_get_policy_path(top->s);
	char *policy_type_str = "Policy";
	const char *primary_path;
	char *s;

	if (log_path == NULL) {
		log_path = "No Log";
	}
	if (policy_path == NULL) {
		primary_path = "No Policy";
	} else {
		if (apol_policy_path_get_type(policy_path) == APOL_POLICY_PATH_TYPE_MODULAR) {
			policy_type_str = "Base";
		}
		primary_path = apol_policy_path_get_primary(policy_path);
	}
	if (asprintf(&s, "seaudit - [Log file: %s] [%s file: %s]", log_path, policy_type_str, primary_path) < 0) {
		toplevel_ERR(top, "%s", strerror(errno));
		return;
	}
	gtk_window_set_title(top->w, s);
	free(s);
}
