gwy_app_wait_finish(void)
{
    if (cancelled) {
        cancelled = FALSE;
        return;
    }

    if (!silent_waiting) {
        g_return_if_fail(dialog != NULL);
        gtk_widget_destroy(dialog);
        g_free(message_prefix);
    }
    dialog = NULL;
    progress = NULL;
    label = NULL;
    message_prefix = NULL;
    wait_widget = NULL;
    silent_waiting = FALSE;
}
