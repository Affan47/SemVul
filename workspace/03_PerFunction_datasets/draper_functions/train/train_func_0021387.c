dec (gint d, const gchar *fmt)
{
    gchar string [32];
    g_snprintf (string, sizeof (string), fmt, d);
    return string;
}
