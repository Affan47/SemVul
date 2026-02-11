color_get_gc(color_t* color)
{
    if (!color->gc)
    {
        GtkWidget* win = gui_get_main_win();
        color->gc = gdk_gc_new(win->window);
        gdk_colormap_alloc_color(gdk_rgb_get_cmap(), &color->c, FALSE, FALSE);
        gdk_gc_set_foreground(color->gc, &color->c);
        if (color->type == COLOR_MARK1 || color->type == COLOR_MARK2)
            gdk_gc_set_function(color->gc, GDK_XOR);
    }
    return color->gc;
}
