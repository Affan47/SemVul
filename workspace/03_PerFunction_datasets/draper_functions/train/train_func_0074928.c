gui_mch_beep(void)
{
#ifdef HAVE_GTK_MULTIHEAD
    GdkDisplay *display;

    if (gui.mainwin != NULL && GTK_WIDGET_REALIZED(gui.mainwin))
	display = gtk_widget_get_display(gui.mainwin);
    else
	display = gdk_display_get_default();

    if (display != NULL)
	gdk_display_beep(display);
#else
    gdk_beep();
#endif
}
