e2_utils_str_stretch (gchar *str)
{
	if (!g_utf8_validate (str, -1, NULL))
		return (g_strdup (str));

	gchar *retval;
	glong len;
	gunichar *conv = g_utf8_to_ucs4_fast (str, -1, &len);

#ifdef __USE_GNU
	gunichar stretch [len * 2];
#else
	gunichar *stretch = NEW (gunichar, len * 2);
	if (stretch != NULL)
#endif
	{
		glong i, j;
		for (i = 0, j = 0; i < len; i++, j++)
		{
			stretch[j] = conv[i];
			stretch[++j] = ' ';
		}
		stretch[--j] = '\0';

		retval = g_ucs4_to_utf8 (stretch, -1, NULL, NULL, NULL);
	}
#ifndef __USE_GNU
	else
		retval = g_strdup (str);

	g_free (stretch);
#endif
	g_free (conv);
	return retval;
}
