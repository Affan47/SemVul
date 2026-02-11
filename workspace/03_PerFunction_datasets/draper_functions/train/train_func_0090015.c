on_logout_clicked (GtkWidget          *button,
                   GsmFailWhaleDialog *fail_dialog)
{
        if (!fail_dialog->priv->debug_mode) {
                g_spawn_command_line_async ("gnome-session-quit --force", NULL);
        }
        gtk_main_quit ();
}
