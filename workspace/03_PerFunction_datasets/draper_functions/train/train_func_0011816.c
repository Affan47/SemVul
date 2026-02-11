store_mixer(struct chan_oss_pvt *o, const char *s)
{
	int i;

	for (i = 0; i < strlen(s); i++) {
		if (!isalnum(s[i]) && strchr(" \t-/", s[i]) == NULL) {
			ast_log(LOG_WARNING, "Suspect char %c in mixer cmd, ignoring:\n\t%s\n", s[i], s);
			return;
		}
	}
	if (o->mixer_cmd)
		ast_free(o->mixer_cmd);
	o->mixer_cmd = ast_strdup(s);
	ast_log(LOG_WARNING, "setting mixer %s\n", s);
}
