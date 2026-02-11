chart_alloc_gcs(chart_priv *c, gchar *colors[])
{
    int i;
    GdkColor color;

    ENTER;
    c->gc_cpu = g_new0( typeof(*c->gc_cpu), c->rows);
    if (c->gc_cpu) {
        for (i = 0; i < c->rows; i++) {
            c->gc_cpu[i] = gdk_gc_new(c->plugin.panel->topgwin->window);
            gdk_color_parse(colors[i], &color);
            gdk_colormap_alloc_color(
                gdk_drawable_get_colormap(c->plugin.panel->topgwin->window),
                &color, FALSE, TRUE);
            gdk_gc_set_foreground(c->gc_cpu[i],  &color);
        }
    }
    RET();
}
