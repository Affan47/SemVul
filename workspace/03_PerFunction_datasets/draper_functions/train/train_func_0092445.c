parse_text(G_GNUC_UNUSED GMarkupParseContext *context,
           const gchar *value,
           G_GNUC_UNUSED gsize value_len,
           gpointer user_data,
           G_GNUC_UNUSED GError **error)
{
    MDTXMLParams *params = (MDTXMLParams*)user_data;
    gchar *line;
    gdouble wavelength;
    gint i;

    if (params->flag == MDT_XML_NONE) {

    }
    else if (params->flag == MDT_XML_LASER_WAVELENGTH) {
        params->laser_wavelength
                           = g_ascii_strtod(g_strdelimit((gchar *)value,
                                                       ",", '.'), NULL);
    }
    else if (params->flag == MDT_XML_UNITS) {
        params->units = atoi(value);
    }
    else if (params->flag == MDT_XML_DATAARRAY) {
        line = (gchar *)value;
        if (!params->res) {

        }
        else {
            for (i = 0; i < params->res; i++) {
                wavelength = g_ascii_strtod(g_strdelimit(line, ",.", '.'), &line);
                line += 2;
                if (params->units == 1) {
                    params->data[i] = 1e-9 * wavelength;
                }
                else if (params->units == 2
                      && params->laser_wavelength > 0.0) {

                    params->data[i]
                        = 1e9 * (1 / params->laser_wavelength
                        - 1 / wavelength);
                }
            }
        }
    }
}
