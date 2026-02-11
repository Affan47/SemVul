drive_button_button_press (GtkWidget      *widget,
			   GdkEventButton *event)
{
    DriveButton *self = DRIVE_BUTTON (widget);


    if (event->button == 1) {
	drive_button_ensure_popup (self);
	if (self->popup_menu) {
	    gtk_menu_popup (GTK_MENU (self->popup_menu), NULL, NULL,
			    position_menu, self,
			    event->button, event->time);
	}
	return TRUE;
    }
    return FALSE;
}
