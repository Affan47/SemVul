gva_mame_verify_roms (const gchar *name,
                      GError **error)
{
        gchar *arguments;
        gchar **stdout_lines;
        gchar **stderr_lines;
        gchar *status = NULL;
        gint exit_status;
        gint ii;

        g_return_val_if_fail (name != NULL, NULL);


        arguments = g_strdup_printf ("-verifyroms %s", name);
        exit_status = gva_mame_command (
                arguments, &stdout_lines, &stderr_lines, error);
        g_free (arguments);

        if (exit_status < 0)
                return NULL;


        for (ii = 0; status == NULL && stdout_lines[ii] != NULL; ii++)
                gva_mame_verify_parse (stdout_lines[ii], NULL, &status);


        for (ii = 0; status == NULL && stderr_lines[ii] != NULL; ii++)
                gva_mame_verify_parse (stderr_lines[ii], NULL, &status);

        g_strfreev (stdout_lines);
        g_strfreev (stderr_lines);

        return status;
}
