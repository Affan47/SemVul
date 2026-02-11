set_button_sensitive(gboolean sens)
{
	if(this_is_an_object((GtkObject*)button))
		gtk_widget_set_sensitive(button, sens);

}
