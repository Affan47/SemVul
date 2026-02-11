update_window_manager_hints(int force_width, int force_height)
{
    static int old_width  = 0;
    static int old_height = 0;
    static int old_min_width  = 0;
    static int old_min_height = 0;
    static int old_char_width  = 0;
    static int old_char_height = 0;

    int width;
    int height;
    int min_width;
    int min_height;


    if (!(force_width && force_height)  &&  init_window_hints_state > 0)
    {

	init_window_hints_state = 2;
	return;
    }


    width  = gui_get_base_width();
    height = gui_get_base_height();
# ifdef FEAT_MENU
    height += tabline_height() * gui.char_height;
# endif
    width  += get_menu_tool_width();
    height += get_menu_tool_height();


    if (force_width && force_height)
    {
	min_width  = force_width;
	min_height = force_height;
    }
    else
    {
	min_width  = width  + MIN_COLUMNS * gui.char_width;
	min_height = height + MIN_LINES   * gui.char_height;
    }


    if (width != old_width
	    || height != old_height
	    || min_width != old_min_width
	    || min_height != old_min_height
	    || gui.char_width != old_char_width
	    || gui.char_height != old_char_height)
    {
	GdkGeometry	geometry;
	GdkWindowHints	geometry_mask;

	geometry.width_inc   = gui.char_width;
	geometry.height_inc  = gui.char_height;
	geometry.base_width  = width;
	geometry.base_height = height;
	geometry.min_width   = min_width;
	geometry.min_height  = min_height;
	geometry_mask	     = GDK_HINT_BASE_SIZE|GDK_HINT_RESIZE_INC
			       |GDK_HINT_MIN_SIZE;


	gtk_window_set_geometry_hints(GTK_WINDOW(gui.mainwin), gui.mainwin,
				      &geometry, geometry_mask);
	old_width       = width;
	old_height      = height;
	old_min_width   = min_width;
	old_min_height  = min_height;
	old_char_width  = gui.char_width;
	old_char_height = gui.char_height;
    }
}
