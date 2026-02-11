control_change_login (EggBuffer *buffer)
{
	gsize offset = 8;
	guint32 res;
	gchar *master;
	gchar *original;

	if (!egg_buffer_get_string (buffer, offset, &offset, &original, egg_secure_realloc)) {
		return GKD_CONTROL_RESULT_FAILED;
	}

	if (!egg_buffer_get_string (buffer, offset, &offset, &master, egg_secure_realloc)) {
		egg_secure_strfree (original);
		return GKD_CONTROL_RESULT_FAILED;
	}

	if (gkd_login_change_lock (original, master))
		res = GKD_CONTROL_RESULT_OK;
	else
		res = GKD_CONTROL_RESULT_DENIED;

	egg_secure_strfree (master);
	egg_secure_strfree (original);
	return res;
}
