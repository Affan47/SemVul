gnc_date_edit_get_date (GNCDateEdit *gde)
{
    struct tm tm;
    time64 retval;

    g_return_val_if_fail (gde != NULL, 0);
    g_return_val_if_fail (GNC_IS_DATE_EDIT (gde), 0);

    tm = gnc_date_edit_get_date_internal (gde);

    return gnc_mktime (&tm);
}
