_g_strvcmp0 (gchar **one, gchar **two)
{
	guint i;
	if (one == two)
		return TRUE;
	if (one == NULL && two != NULL)
		return FALSE;
	if (one != NULL && two == NULL)
		return FALSE;
	if (g_strv_length (one) != g_strv_length (two))
		return FALSE;
	for (i = 0; one[i] != NULL; i++) {
		if (g_strcmp0 (one[i], two[i]) != 0)
			return FALSE;
	}
	return TRUE;
}
