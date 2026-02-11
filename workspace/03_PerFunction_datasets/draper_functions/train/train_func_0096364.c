on_listitem_button_press (GtkWidget * widget, GdkEvent * event,
			  tListItem * parent)
{
	if (!parent->selected)
	{
		playsound (SND_BUTTONDOWN);
	}

	return TRUE;
}
