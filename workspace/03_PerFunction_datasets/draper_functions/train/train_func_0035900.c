gwy_tool_roughness_Xz(GwyDataLine *data_line)
{
    gdouble Xz = 0.0;
    GwyDataLine *dl;
    gint i, samp;
    gdouble *peaks;

    g_return_val_if_fail(GWY_IS_DATA_LINE(data_line), Xz);

    dl = gwy_data_line_new_alike(data_line, FALSE);
    gwy_data_line_copy(data_line, dl);

    samp = dl->res;
    peaks = g_new0(gdouble, 5);

    gwy_tool_roughness_peaks(data_line, peaks, 1, samp, 0, 5, FALSE);
    for (i = 0; i < 5; i++)
        Xz += peaks[i];

    gwy_data_line_multiply(dl, -1.0);
    gwy_tool_roughness_peaks(data_line, peaks, 1, samp, 0, 5, FALSE);
    for (i = 0; i < 5; i++)
        Xz += peaks[i];

    g_free(peaks);
    g_object_unref(dl);

    return Xz/5.0;
}
