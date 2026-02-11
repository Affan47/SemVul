gwy_gl_material_parse_component(gchar *line,
                                GwyRGBA *rgba)
{
    gchar *end;

    rgba->r = g_ascii_strtod(line, &end);
    if (end == line)
        return FALSE;
    line = end;
    rgba->g = g_ascii_strtod(line, &end);
    if (end == line)
        return FALSE;
    line = end;
    rgba->b = g_ascii_strtod(line, &end);
    if (end == line)
        return FALSE;
    line = end;
    rgba->a = g_ascii_strtod(line, &end);
    if (end == line)
        return FALSE;

    return TRUE;
}
