convert_unit(GwySIUnit *unit)
{
    gchar *str = gwy_si_unit_get_string(unit, GWY_SI_UNIT_FORMAT_PLAIN);
    const gchar *convstr;


    if (gwy_stramong(str, "A", "C", "eV", "Hz", "K", "m", "m/s", "N", "N/m",
                     "Pa", "s", "V", NULL))
        return str;

    if (gwy_strequal(str, "deg"))
        convstr = "degree";
    else if (gwy_strequal(str, "cps"))
        convstr = "c/s";
    else if (gwy_strequal(str, ""))
        convstr = "d";
    else
        convstr = "n";

    g_free(str);
    return g_strdup(convstr);
}
