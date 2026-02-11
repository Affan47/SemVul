data_tostring (XDMCPData *data)
{
    GString *s;
    guint16 i;
    gchar *string;

    s = g_string_new ("");
    for (i = 0; i < data->length; i++)
        g_string_append_printf (s, "%02X", data->data[i]);
    string = s->str;
    g_string_free (s, FALSE);

    return string;
}
