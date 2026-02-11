project_open_existing (const gchar* filename) {
    gchar* content = NULL;
    GError* err = NULL;

    if (!g_file_get_contents (filename, &content, NULL, &err)) {
        slog (L_ERROR, "%s\n", err->message);
        return FALSE;
    }

    if (!project_file_integrity (content)) return FALSE;
    if (!project_load_files (filename, content)) return FALSE;

    gummi->project->projfile = g_strdup (filename);

    return TRUE;
}
