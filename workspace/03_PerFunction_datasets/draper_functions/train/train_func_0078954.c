cm_tdbusm_get_bp(DBusMessage *msg, void *parent, dbus_bool_t *b, char **p)
{
	DBusError err;
	*p = NULL;
	dbus_error_init(&err);
	if (dbus_message_get_args(msg, &err,
				  DBUS_TYPE_BOOLEAN, b,
				  DBUS_TYPE_OBJECT_PATH, p,
				  DBUS_TYPE_INVALID)) {
		*p = *p ? talloc_strdup(parent, *p) : NULL;
		return 0;
	} else {
		if (dbus_error_is_set(&err)) {
			dbus_error_free(&err);
			dbus_error_init(&err);
		}
		return -1;
	}
}
