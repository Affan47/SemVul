bs_window_pixmap_render_new(GdkWindow *window)
{
    BSWindowPixmapRender *bspmr;

    bspmr = (BSWindowPixmapRender *)g_malloc(sizeof(BSWindowPixmapRender));
    bspmr->pixmap = NULL;
    bspmr->window = window;
    g_object_ref(window);
    bspmr->src_picture = None;
    bspmr->dst_picture = None;
    bspmr->damage = None;
    bspmr->changed_callback = NULL;
    bspmr->pm_width = -1;
    bspmr->pm_height = -1;

    if (gdk_window_is_visible(bspmr->window))
        window_first_showing(bspmr);
    else
        gdk_window_set_events(bspmr->window,
                              gdk_window_get_events(bspmr->window) |
                              GDK_STRUCTURE_MASK);

    gdk_window_add_filter(bspmr->window, event_filter, bspmr);
    return bspmr;
}
