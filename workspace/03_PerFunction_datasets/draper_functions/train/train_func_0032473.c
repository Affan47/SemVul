find_key_press_event(
		GtkWidget	*widget UNUSED,
		GdkEventKey	*event,
		SharedFindReplace *frdp)
{


    if (event->state & (GDK_CONTROL_MASK | GDK_SHIFT_MASK))
	return FALSE;


    if (event->keyval == GDK_Escape)
    {
	gtk_widget_hide(frdp->dialog);

	return TRUE;
    }


    return FALSE;
}
