append_query_param (gpointer key, gpointer value, gpointer user_data)
{
    GString *params = (GString*) user_data;
    char *encoded_val, *encoded_key;
    char *param;

    encoded_val = soup_uri_encode (value, EXTRA_CHARS_ENCODE);
    encoded_key = soup_uri_encode (key, EXTRA_CHARS_ENCODE);

    param = g_strdup_printf ("%s=%s", encoded_key, encoded_val);
    g_free (encoded_key);
    g_free (encoded_val);


    if (params->len)
        g_string_append_c (params, '&');
    g_string_append (params, param);
}
