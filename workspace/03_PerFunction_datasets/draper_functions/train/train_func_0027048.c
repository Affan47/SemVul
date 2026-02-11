rsvg_node_image_draw (RsvgNode * self, RsvgDrawingCtx * ctx, int dominate)
{
    RsvgNodeImage *z = (RsvgNodeImage *) self;
    unsigned int aspect_ratio = z->preserve_aspect_ratio;
    gdouble x, y, w, h;
    cairo_surface_t *surface = z->surface;

    if (surface == NULL)
        return;

    x = _rsvg_css_normalize_length (&z->x, ctx, 'h');
    y = _rsvg_css_normalize_length (&z->y, ctx, 'v');
    w = _rsvg_css_normalize_length (&z->w, ctx, 'h');
    h = _rsvg_css_normalize_length (&z->h, ctx, 'v');

    rsvg_state_reinherit_top (ctx, z->super.state, dominate);

    rsvg_push_discrete_layer (ctx);

    if (!rsvg_current_state (ctx)->overflow && (aspect_ratio & RSVG_ASPECT_RATIO_SLICE)) {
        rsvg_add_clipping_rect (ctx, x, y, w, h);
    }

    rsvg_preserve_aspect_ratio (aspect_ratio,
                                (double) cairo_image_surface_get_width (surface),
                                (double) cairo_image_surface_get_height (surface),
                                &w, &h, &x, &y);

    rsvg_render_surface (ctx, surface, x, y, w, h);

    rsvg_pop_discrete_layer (ctx);
}
