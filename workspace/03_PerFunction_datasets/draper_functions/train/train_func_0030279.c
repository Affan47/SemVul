xaccTransIsReadonlyByPostedDate(const Transaction *trans)
{
    GDate *threshold_date;
    GDate trans_date;
    const QofBook *book = xaccTransGetBook (trans);
    gboolean result;
    g_assert(trans);

    if (!qof_book_uses_autoreadonly(book))
    {
        return FALSE;
    }

    threshold_date = qof_book_get_autoreadonly_gdate(book);
    g_assert(threshold_date);
    trans_date = xaccTransGetDatePostedGDate(trans);


    if (g_date_compare(&trans_date, threshold_date) < 0)
    {

        result = TRUE;
    }
    else
    {
        result = FALSE;
    }
    g_date_free(threshold_date);
    return result;
}
