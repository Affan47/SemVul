bool_change_append(seaudit_log_t * log, seaudit_bool_message_t * boolm, const char *name, int value)
{
	char *s = strdup(name);
	seaudit_bool_message_change_t *bc = NULL;
	int error;
	if (s == NULL || apol_bst_insert_and_get(log->bools, (void **)&s, NULL) < 0) {
		error = errno;
		free(s);
		ERR(log, "%s", strerror(error));
		errno = error;
		return -1;
	}
	if ((bc = calloc(1, sizeof(*bc))) == NULL || apol_vector_append(boolm->changes, bc) < 0) {
		error = errno;
		free(s);
		ERR(log, "%s", strerror(error));
		errno = error;
		return -1;
	}
	bc->boolean = s;
	bc->value = value;
	return 0;
}
