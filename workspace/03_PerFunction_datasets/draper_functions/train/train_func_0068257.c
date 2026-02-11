popup_menu_position_func(GtkMenu *menu UNUSED,
			 gint *x, gint *y,
			 gboolean *push_in UNUSED,
			 gpointer user_data UNUSED)
{
    gdk_window_get_origin(gui.drawarea->window, x, y);

    if (popup_mouse_pos)
    {
	int	mx, my;

	gui_mch_getmouse(&mx, &my);
	*x += mx;
	*y += my;
    }
    else if (curwin != NULL && gui.drawarea != NULL && gui.drawarea->window != NULL)
    {

	*x += FILL_X(W_WINCOL(curwin) + curwin->w_wcol + 1) + 1;
	*y += FILL_Y(W_WINROW(curwin) + curwin->w_wrow + 1) + 1;
    }
}
