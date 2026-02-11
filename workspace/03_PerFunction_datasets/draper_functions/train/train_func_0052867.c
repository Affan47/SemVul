writer ( const gchar *buf, gsize count, GError **error, gpointer data)
{
    if (count == gvwrite((GVJ_t *)data, buf, count))
        return TRUE;
    return FALSE;
}
