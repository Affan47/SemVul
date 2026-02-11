remote_object_print (RemoteObject *obj,
		     const char *text,
		     GError **error)
{
	if (hexchat_set_context (ph, obj->context)) {
		hexchat_print (ph, text);
	}
	return TRUE;
}
