on_pixbutton2_enter_notify (GtkWidget * widget, GdkEventCrossing * event,
			    tPixButton2 * parent)
{
	parent->mousein = TRUE;
	if (event->mode!=GDK_CROSSING_NORMAL)
		return true;

	if (!parent->enable)
		return true;
	if (!parent->pressed)
	{
		playsound (SND_BUTTONACTIVE);
		gtk_image_set_from_pixmap (GTK_IMAGE (parent->pixmap_widget),
				parent->pix_active, (GdkBitmap *) NULL);
	}
	return true;
}
