construct_rgi_names(const gchar *pluginname)
{
    gchar **rginames;
    gchar *pos;
    gint len;

    pos = strrchr(pluginname, '.');
    rginames = g_new0(gchar*, pos ? 5 : 3);
    rginames[0] = g_strconcat(pluginname, ".rgi", NULL);
    rginames[1] = g_strconcat(pluginname, ".RGI", NULL);
    if (pos) {
        len = pos - pluginname;
        rginames[2] = g_new(gchar, len + 5);
        strncpy(rginames[2], pluginname, len + 1);
        strncpy(rginames[2] + len + 1, "rgi", 4);
        rginames[3] = g_new(gchar, len + 5);
        strncpy(rginames[3], pluginname, len + 1);
        strncpy(rginames[3] + len + 1, "RGI", 4);
    }

    return rginames;
}
