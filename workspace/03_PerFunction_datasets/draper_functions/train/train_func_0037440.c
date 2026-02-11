get_bare_jid(const gchar *full_jid)
{
    gchar *pos;

    for (pos = (gchar *)full_jid; *pos && *pos != '/'; pos ++);

    return g_strndup(full_jid, pos - full_jid);
}
