gwy_axis_format_label(GwyAxis *axis,
                      PangoLayout *layout)
{
    gchar *units;
    GString *plotlabel;

    plotlabel = g_string_new(axis->label_text->str);
    units = gwy_si_unit_get_string(axis->unit, GWY_SI_UNIT_FORMAT_MARKUP);
    if ((axis->magnification_string && axis->magnification_string->len > 0)
        || *units) {
        g_string_append(plotlabel, " [");
        if (axis->magnification_string && axis->magnification_string->len)
            g_string_append(plotlabel, axis->magnification_string->str);
        else
            g_string_append(plotlabel, units);
        g_string_append(plotlabel, "]");
    }
    g_free(units);

    pango_layout_set_font_description(layout, axis->par.major_font);
    pango_layout_set_markup(layout, plotlabel->str, plotlabel->len);
    g_string_free(plotlabel, TRUE);
}
