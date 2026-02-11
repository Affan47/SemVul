gva_mame_delete_save_state (const gchar *name)
{
        gchar *filename;

        filename = gva_mame_get_save_state_file (name);

        if (filename != NULL && g_unlink (filename) < 0)
                g_warning (
                        "Could not delete %s: %s",
                        filename, g_strerror (errno));

        g_free (filename);
}
