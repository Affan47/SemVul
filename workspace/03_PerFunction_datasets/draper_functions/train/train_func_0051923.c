gwy_si_unit_get_format_with_resolution(GwySIUnit *siunit,
                                       GwySIUnitFormatStyle style,
                                       gdouble maximum,
                                       gdouble resolution,
                                       GwySIValueFormat *format)
{
    const GwySIStyleSpec *spec;

    gwy_debug("");
    g_return_val_if_fail(GWY_IS_SI_UNIT(siunit), NULL);

    spec = gwy_si_unit_find_style_spec(style);
    if (!format)
        format = (GwySIValueFormat*)g_new0(GwySIValueFormat, 1);

    maximum = fabs(maximum);
    resolution = fabs(resolution);
    if (!maximum) {
        format->magnitude = 1;
        format->precision = 2;
    }
    else
        format->magnitude = gwy_math_humanize_numbers(resolution, maximum,
                                                      &format->precision);
    siunit->power10 = GWY_ROUND(log10(format->magnitude));
    format->units_gstring = gwy_si_unit_format(siunit, spec,
                                               format->units_gstring);
    format->units = format->units_gstring->str;

    return format;
}
