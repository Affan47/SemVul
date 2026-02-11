gwy_data_line_cda(GwyDataLine *data_line,
                  GwyDataLine *target_line,
                  gdouble ymin, gdouble ymax,
                  gint nsteps)
{
    g_return_if_fail(GWY_IS_DATA_LINE(data_line));
    g_return_if_fail(GWY_IS_DATA_LINE(target_line));

    gwy_data_line_da(data_line, target_line, ymin, ymax, nsteps);
    gwy_data_line_cumulate(target_line);
}
