gl_ui_cmd_file_quit (GtkAction *action,
                     glWindow  *window)
{
        gl_debug (DEBUG_COMMANDS, "START");

        g_return_if_fail (action && GTK_IS_ACTION(action));
        g_return_if_fail (window && GL_IS_WINDOW(window));

        gl_file_exit ();

        gl_debug (DEBUG_COMMANDS, "END");
}
