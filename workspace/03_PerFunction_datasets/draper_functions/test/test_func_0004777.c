charset_track_charset_from_utf8 (Track *s, const gchar *str)
{
    gchar *charset;
    const gchar *locale_charset;
    gchar *result;
    ExtraTrackData *etd;

    g_return_val_if_fail (s, NULL);
    g_return_val_if_fail (s->userdata, NULL);

    if (str == NULL) return NULL;

    etd = s->userdata;

    if (etd->charset && strlen (etd->charset))
	   charset = g_strdup(etd->charset);
    else
	charset = prefs_get_string("charset");

    if (!charset || !strlen (charset))
    {
	g_free(charset);
	g_get_charset (&locale_charset);
	charset = g_strdup(locale_charset);
    }

    result = charset_to_charset ("UTF-8", charset, str);
    g_free(charset);
    return result;
}
