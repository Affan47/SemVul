type_to_title(guint type)
{
    const gchar *title;

    title = gwy_enuml_to_string(type,
                                "Height", 0,
                                "Current", 1,
                                "FFM", 2,
                                "Spect", 3,
                                "SpectV", 4,
                                "ADC1", 5,
                                "ADC2", 6,
                                "TipV", 7,
                                "DAC1", 8,
                                "DAC2", 9,
                                "ZPiezo", 10,
                                "Height error", 11,
                                "Linearized Z", 12,
                                "Feedback", 13,
                                NULL);
    if (*title)
        return g_strdup(title);

    return NULL;
}
