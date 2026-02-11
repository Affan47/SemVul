gui_mch_flush(void)
{
#ifdef HAVE_GTK_MULTIHEAD
    if (gui.mainwin != NULL && GTK_WIDGET_REALIZED(gui.mainwin))
	gdk_display_sync(gtk_widget_get_display(gui.mainwin));
#else
    gdk_flush();
#endif


    if (gui.drawarea != NULL && gui.drawarea->window != NULL)
	gdk_window_process_updates(gui.drawarea->window, FALSE);
}
