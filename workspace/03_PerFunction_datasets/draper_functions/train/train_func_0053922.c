cm_tdbusm_get_sss(DBusMessage *msg, void *parent, char **s1, char **s2,
		  char **s3)
{
	DBusError err;
	*s1 = NULL;
	*s2 = NULL;
	*s3 = NULL;
	dbus_error_init(&err);
	if (dbus_message_get_args(msg, &err,
				  DBUS_TYPE_STRING, s1,
				  DBUS_TYPE_STRING, s2,
				  DBUS_TYPE_STRING, s3,
				  DBUS_TYPE_INVALID)) {
		*s1 = *s1 ? talloc_strdup(parent, *s1) : NULL;
		*s2 = *s2 ? talloc_strdup(parent, *s2) : NULL;
		*s3 = *s3 ? talloc_strdup(parent, *s3) : NULL;
		return 0;
	} else {
		if (dbus_error_is_set(&err)) {
			dbus_error_free(&err);
			dbus_error_init(&err);
		}
		return -1;
	}
}
