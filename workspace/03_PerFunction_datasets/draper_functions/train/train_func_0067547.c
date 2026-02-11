pk_strvequal (gchar **id1, gchar **id2)
{
	guint i;
	guint length1;
	guint length2;

	if (id1 == NULL && id2 == NULL)
		return TRUE;

	if (id1 == NULL || id2 == NULL) {
		g_debug ("GStrv compare invalid '%p' and '%p'", id1, id2);
		return FALSE;
	}


	length1 = g_strv_length (id1);
	length2 = g_strv_length (id2);
	if (length1 != length2)
		return FALSE;


	for (i=0; i<length1; i++) {
		if (g_strcmp0 (id1[i], id2[i]) != 0)
			return FALSE;
	}

	return TRUE;
}
