convert_string_1 (const gchar *string, gssize length, const gchar *from_codeset,
                         const gchar *to_codeset, const gboolean display_error)
{
    gchar *output;
    GError *error = NULL;
    gsize bytes_written;

    g_return_val_if_fail (string != NULL, NULL);

    output = g_convert(string, length, to_codeset, from_codeset, NULL, &bytes_written, &error);


    if (output == NULL)
    {
        gchar *escaped_str = g_strescape(string, NULL);
        if (display_error)
        {
            Log_Print(LOG_ERROR,"convert_string(): Failed conversion from charset '%s' to '%s'. "
                      "String '%s'. Errcode %d (%s).",
                      from_codeset, to_codeset, escaped_str, error->code, error->message);
        }
        g_free(escaped_str);
        g_error_free(error);


        if ( (g_ascii_strcasecmp(to_codeset, "UTF-8"))
        ||   (g_utf8_validate(string, -1, NULL)) )
        {
            return g_strdup(string);
        }
    }else
    {


        gchar *new_output;
        new_output = g_realloc (output, bytes_written + 2);
        if (new_output != NULL)
        {
            output = new_output;
            output[bytes_written] = output[bytes_written + 1] = 0;
        }
    }


    return output;
}
