SetFont(Font &scint_font) {

	if (Created() && PFont(scint_font)->pfd) {

#if GTK_CHECK_VERSION(3,0,0)
		gtk_widget_override_font(PWidget(list), PFont(scint_font)->pfd);
#else
		gtk_widget_modify_font(PWidget(list), PFont(scint_font)->pfd);
#endif
	}
}
