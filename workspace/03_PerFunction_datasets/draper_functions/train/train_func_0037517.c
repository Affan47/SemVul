db_parser_bind_text (sqlite3_stmt *stmt,
                     const gchar *param,
                     const gchar *value)
{
        gint index;
        gint errcode;
        gchar *utf8;
        GError *error = NULL;

        index = sqlite3_bind_parameter_index (stmt, param);
        utf8 = g_locale_to_utf8 (value, -1, NULL, NULL, &error);
        gva_error_handle (&error);

        g_return_if_fail (utf8 != NULL);
        errcode = sqlite3_bind_text (stmt, index, utf8, -1, g_free);

        if (errcode != SQLITE_OK)
        {
                gva_db_set_error (&error, 0, NULL);
                gva_error_handle (&error);
        }
}
