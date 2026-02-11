gui_mch_get_screen_dimensions(int *screen_w, int *screen_h)
{
#ifdef HAVE_GTK_MULTIHEAD
    GdkScreen* screen;

    if (gui.mainwin != NULL && gtk_widget_has_screen(gui.mainwin))
	screen = gtk_widget_get_screen(gui.mainwin);
    else
	screen = gdk_screen_get_default();

    *screen_w = gdk_screen_get_width(screen);
    *screen_h = gdk_screen_get_height(screen) - p_ghr;
#else
    *screen_w = gdk_screen_width();


    *screen_h = gdk_screen_height() - p_ghr;
#endif


    *screen_w -= get_menu_tool_width();
    *screen_h -= get_menu_tool_height();
}
