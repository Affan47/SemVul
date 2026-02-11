print_hint(const char *error, const char *message)
{
	char *text = NULL;
	void *ctx;
	ctx = talloc_new(NULL);
	text = cm_tdbusm_hint(ctx, error, message);
	if ((text == NULL) &&
	    (strncmp(error, CM_DBUS_ERROR_BASE,
		     strlen(CM_DBUS_ERROR_BASE)) == 0)) {
		text = talloc_asprintf(ctx, "%s\n", _(message));
	}
	if (text != NULL) {
		printf("%s", _(text));
	}
	talloc_free(ctx);
	return text ? hint_found : hint_unknown;
}
