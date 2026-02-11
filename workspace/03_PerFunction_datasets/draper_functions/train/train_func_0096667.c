entry_key_press (GtkWidget   *widget,
                 GdkEventKey *event,
                 GSLockPlug  *plug)
{
        restart_cancel_timeout (plug);


        if (gtk_widget_get_visible (plug->priv->auth_prompt_entry) &&
            gtk_widget_get_sensitive (plug->priv->auth_prompt_entry)) {
                return FALSE;
        }

        if (strcmp (event->string, "") == 0) {
                return FALSE;
        }

        queue_key_event (plug, event);

        return TRUE;
}
