ario_util_copy_file (const char *src_uri,
                     const char *dest_uri)
{
        ARIO_LOG_FUNCTION_START;
        gchar *contents;
        gsize length;


        if (! ario_file_get_contents (src_uri,
                                      &contents,
                                      &length,
                                      NULL)) {
                return;
        }


        ario_file_set_contents (dest_uri,
                                contents,
                                length,
                                NULL);
        g_free (contents);
}
