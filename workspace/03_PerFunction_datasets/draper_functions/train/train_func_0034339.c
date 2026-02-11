snippets_set_default (GuSnippets* sc) {
    GError* err = NULL;
    gchar* snip = g_build_filename (GUMMI_DATA, "snippets", "snippets.cfg", NULL);
    GList* current = sc->closure_data;


    while (current) {
        gtk_accel_group_disconnect (sc->accel_group,
                TUPLE2 (current->data)->second);
        slog (L_DEBUG, "Accelerator for `%s' disconnected\n",
                TUPLE2 (current->data)->first);
        current = g_list_next (current);
    }
    g_list_free (sc->closure_data);
    sc->closure_data = NULL;

    if (!utils_copy_file (snip, sc->filename, &err)) {
        slog (L_G_ERROR, "can't open snippets file for writing, snippets may "
                "not work properly\n");
        g_error_free (err);
    } else {
        snippets_load (sc);
    }
    g_free (snip);
}
