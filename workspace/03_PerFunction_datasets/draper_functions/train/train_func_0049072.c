button_release_event_cb(GtkWidget* , GdkEventButton* ,
        gpointer data)
{
    GNASH_REPORT_FUNCTION;
    GnashView *view = GNASH_VIEW(data);
    if (view->stage.get() == NULL)
        return FALSE;

    view->stage->mouseClick(false);

    return TRUE;
}
