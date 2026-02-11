draw_grid(GtkPrintContext *context, gint width, gint height, const gchar *font)
{
    const double dash_pattern[2] = { 1.0, 5.0 };
    PangoFontDescription *desc;
    PangoLayout *layout;
    cairo_t *cr;
    gchar *text;
    gint i;


    layout = gtk_print_context_create_pango_layout(context);
    desc = pango_font_description_from_string(font);
    pango_layout_set_font_description(layout, desc);
    pango_font_description_free(desc);
    pango_layout_set_alignment(layout, PANGO_ALIGN_LEFT);
    pango_layout_set_width(layout, -1);


    cr = gtk_print_context_get_cairo_context(context);
    cairo_save(cr);
    cairo_set_line_width(cr, 1.0);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_dash(cr, dash_pattern, 2, 0);


    for (i = -200; i < (height + 200); i += 50)
    {
        text = g_strdup_printf("%d", (int)i);
        cairo_move_to(cr, -200, i);
        cairo_line_to(cr, width + 200, i);
        cairo_stroke(cr);
        pango_layout_set_text(layout, text, -1);
        cairo_move_to(cr, 0, i);
        pango_cairo_show_layout(cr, layout);
        g_free(text);
    }


    for (i = -200; i < (width + 200); i += 50)
    {
        text = g_strdup_printf("%d", (int)i);
        cairo_move_to(cr, i, -200);
        cairo_line_to(cr, i, height + 200);
        cairo_stroke(cr);
        pango_layout_set_text(layout, text, -1);
        cairo_move_to(cr, i, 0);
        pango_cairo_show_layout(cr, layout);
        g_free(text);
    }


    cairo_restore(cr);
    g_object_unref(layout);
}
