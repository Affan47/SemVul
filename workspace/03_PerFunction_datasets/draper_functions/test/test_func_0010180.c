set_cursor_visibility (GsdCursorManager *manager,
                       gboolean          visible)
{
        g_debug ("Attempting to %s the cursor", visible ? "show" : "hide");

        if (manager->priv->cursor_shown == visible)
                return;

        gdk_error_trap_push ();
        foreach_screen (manager, set_cursor_visibility_foreach, GINT_TO_POINTER (visible));
        if (gdk_error_trap_pop ()) {
                g_warning ("An error occurred trying to %s the cursor",
                           visible ? "show" : "hide");
        }

        manager->priv->cursor_shown = visible;
}
