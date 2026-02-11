extract_units(const gchar *label,
              gdouble *q)
{
    GwySIUnit *unit;
    gint power10;
    const gchar *s;
    gchar *t;

    if ((s = strchr(label, '['))) {
        t = g_strdup(s + 1);
        if (strchr(t, ']'))
            *strchr(t, ']') = '\0';
        unit = gwy_si_unit_new_parse(t, &power10);
        g_free(t);
    }
    else
        unit = gwy_si_unit_new_parse(label, &power10);

    *q = pow10(power10);
    return unit;
}
