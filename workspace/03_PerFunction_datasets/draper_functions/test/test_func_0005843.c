gsd_osd_window_draw (GsdOsdDrawContext *ctx,
                     cairo_t           *cr)
{
        gdouble          corner_radius;
        GdkRGBA          acolor;


        corner_radius = ctx->size / 10;
        gsd_osd_window_draw_rounded_rectangle (cr, 1.0, 0.0, 0.0, corner_radius, ctx->size - 1, ctx->size - 1);

        gtk_style_context_get_background_color (ctx->style, GTK_STATE_NORMAL, &acolor);
        gdk_cairo_set_source_rgba (cr, &acolor);
        cairo_fill (cr);

        switch (ctx->action) {
        case GSD_OSD_WINDOW_ACTION_VOLUME:
                draw_action_volume (ctx, cr);
                break;
        case GSD_OSD_WINDOW_ACTION_CUSTOM:
                draw_action_custom (ctx, cr);
                break;
        default:
                break;
        }
}
