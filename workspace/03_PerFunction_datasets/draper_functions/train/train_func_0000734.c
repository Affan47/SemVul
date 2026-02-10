lock_screen (GsmInhibitDialog *dialog)
{
        GError *error;
        error = NULL;
        g_spawn_command_line_async ("gnome-screensaver-command --lock", &error);
        if (error != NULL) {
                g_warning ("Couldn't lock screen: %s", error->message);
                g_error_free (error);
        }
}
