cm_tdbusm_get_sd(DBusMessage *msg, void *parent,
		 char **s, struct cm_tdbusm_dict ***d)
{
	struct cm_tdbusm_dict **tdicts, **dicts, **tmp;
	DBusMessageIter args, array;
	int i, n_dicts;
	*d = NULL;
	dicts = NULL;
	n_dicts = 0;
	memset(&args, 0, sizeof(args));
	if (dbus_message_iter_init(msg, &args)) {
		if (dbus_message_iter_get_arg_type(&args) != DBUS_TYPE_STRING) {
			return -1;
		}
		dbus_message_iter_get_basic(&args, s);
		if (*s == NULL) {
			return -1;
		}
		*s = talloc_strdup(parent, *s);
		if (!dbus_message_iter_has_next(&args) ||
		    !dbus_message_iter_next(&args)) {
			return -1;
		}
		if (dbus_message_iter_get_arg_type(&args) != DBUS_TYPE_ARRAY) {
			return -1;
		}
		memset(&array, 0, sizeof(array));
		dbus_message_iter_recurse(&args, &array);
		tdicts = cm_tdbusm_get_d_array(&array, parent);
		if (tdicts != NULL) {
			for (i = 0; tdicts[i] != NULL; i++) {
				continue;
			}
			tmp = talloc_realloc(parent, dicts,
					     struct cm_tdbusm_dict *,
					     n_dicts + i + 1);
			if (tmp != NULL) {
				memcpy(tmp + n_dicts,
				       tdicts,
				       i * sizeof(tdicts[0]));
				n_dicts += i;
				tmp[n_dicts] = NULL;
				dicts = tmp;
			} else {
				talloc_free(tdicts);
				talloc_free(dicts);
				return -1;
			}
		}
		if (dbus_message_iter_has_next(&args)) {
			if (!dbus_message_iter_next(&args)) {
				talloc_free(dicts);
				return -1;
			}
		}
		*d = dicts;
		return 0;
	}
	return -1;
}
