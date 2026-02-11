gnc_gdate_set_fiscal_year_start (GDate *date,
                                 const GDate *fy_end)
{
    GDate temp;
    gboolean new_fy;

    g_return_if_fail(date);
    g_return_if_fail(fy_end);


    temp = *fy_end;
    g_date_set_year(&temp, g_date_get_year(date));


    new_fy = (g_date_compare(date, &temp) > 0);


    *date = temp;
    g_date_add_days(date, 1);
    if (!new_fy)
        g_date_subtract_years(date, 1);
}
