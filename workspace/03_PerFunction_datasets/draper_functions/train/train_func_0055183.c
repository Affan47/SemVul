CubeRolloutPresets(GtkWidget * pw, cubehintdata * pchd)
{
    const gchar *preset;
    gchar *file = NULL;
    gchar *path = NULL;
    gchar *command = NULL;

    preset = (const gchar *) g_object_get_data(G_OBJECT(pw), "user_data");
    file = g_strdup_printf("%s.rol", preset);
    path = g_build_filename(szHomeDirectory, "rol", file, NULL);
    if (g_file_test(path, G_FILE_TEST_IS_REGULAR)) {
        command = g_strdup_printf("load commands \"%s\"", path);
        outputoff();
        UserCommand(command);
        outputon();
        CubeAnalysisRollout(pw, pchd);
    } else {
        outputerrf(_("You need to save a preset as \"%s\""), file);
        CubeAnalysisRolloutSettings(pw, NULL);
    }
    g_free(file);
    g_free(path);
    g_free(command);
}
