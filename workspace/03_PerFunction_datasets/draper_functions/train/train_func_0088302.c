blink_cb(gpointer data UNUSED)
{
    if (blink_state == BLINK_ON)
    {
	gui_undraw_cursor();
	blink_state = BLINK_OFF;
	blink_timer = gtk_timeout_add((guint32)blink_offtime,
				   (GtkFunction) blink_cb, NULL);
    }
    else
    {
	gui_update_cursor(TRUE, FALSE);
	blink_state = BLINK_ON;
	blink_timer = gtk_timeout_add((guint32)blink_ontime,
				   (GtkFunction) blink_cb, NULL);
    }

    return FALSE;
}
