get_markup_date (PopplerAnnotMarkup *poppler_annot)
{
    GDate *date;
    struct tm t;
    time_t timet;

    date = poppler_annot_markup_get_date (poppler_annot);
    if (!date)
	    return NULL;

    g_date_to_struct_tm (date, &t);
    g_date_free (date);

    timet = mktime (&t);
    return timet == (time_t) - 1 ? NULL : pgd_format_date (timet);
}
