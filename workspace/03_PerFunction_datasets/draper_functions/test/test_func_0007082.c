open_ro_view(Glib::ustring mountPoint)
{
	GError *error = NULL ;
	GdkScreen *gscreen = NULL ;

	Glib::ustring uri = "file:" + mountPoint ;

	gscreen = gdk_screen_get_default() ;

#ifdef HAVE_GTK_SHOW_URI
	gtk_show_uri( gscreen, uri .c_str(), gtk_get_current_event_time(), &error ) ;
#else
	Glib::ustring command = "gnome-open " + uri ;
	gdk_spawn_command_line_on_screen( gscreen, command .c_str(), &error ) ;
#endif

	if ( error != NULL )
	{
		Glib::ustring sec_text(_("Error:"));
		sec_text.append("\n");
		sec_text.append(error ->message);
		sec_text.append("\n");
		sec_text.append("\n");


		sec_text.append(_("The file system is mounted on:"));
		sec_text.append("\n");
		sec_text.append("<b>"+mountPoint+"</b>");

		Gtk::MessageDialog dialog( *this
		                         , _( "Unable to open the default file manager" )
		                         , false
		                         , Gtk::MESSAGE_ERROR
		                         , Gtk::BUTTONS_OK
		                         , true
		                         ) ;
		dialog .set_secondary_text( sec_text, true ) ;
		dialog .run() ;
	}
}
