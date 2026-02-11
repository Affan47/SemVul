GEN_map_window_refresh_if_display_type(GEN_map_window *win, AW_CL cl_display_type_mask) {
    int display_type_mask = int(cl_display_type_mask);
    int my_display_type   = win->get_graphic()->get_display_style();

    if (display_type_mask & DISPLAY_TYPE_BIT(my_display_type)) {
        AWT_canvas *canvas = win->get_canvas();
        canvas->refresh();
    }
}
