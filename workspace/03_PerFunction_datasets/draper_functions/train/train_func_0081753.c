gl_ui_cmd_edit_delete (GtkAction *action,
                       glWindow  *window)
{
        gl_debug (DEBUG_COMMANDS, "START");

        g_return_if_fail (action && GTK_IS_ACTION(action));
        g_return_if_fail (window && GL_IS_WINDOW(window));

        gl_label_delete_selection (GL_VIEW(window->view)->label);

        gl_debug (DEBUG_COMMANDS, "END");
}
