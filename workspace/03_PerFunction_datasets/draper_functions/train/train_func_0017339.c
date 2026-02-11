remote_object_send_modes (RemoteObject *obj,
			  const char *targets[],
			  int modes_per_line,
			  char sign,
			  char mode,
			  GError **error)
{
	if (hexchat_set_context (ph, obj->context)) {
		hexchat_send_modes (ph, targets,
				  g_strv_length ((char**)targets),
				  modes_per_line,
				  sign, mode);
	}
	return TRUE;
}
