eek_preview_leave_cb( GtkWidget* widget, GdkEventCrossing* event )
{
    if ( gtk_get_event_widget( (GdkEvent*)event ) == widget ) {
        EekPreview* preview = EEK_PREVIEW(widget);
        preview->_within = FALSE;
        gtk_widget_set_state( widget, GTK_STATE_NORMAL );
    }
    return FALSE;
}
