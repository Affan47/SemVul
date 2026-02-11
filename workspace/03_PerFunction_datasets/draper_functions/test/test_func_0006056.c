qof_date_completion_set(QofDateCompletion dc, int backmonths)
{
    if (dc == QOF_DATE_COMPLETION_THISYEAR ||
            dc == QOF_DATE_COMPLETION_SLIDING)
    {
        dateCompletion = dc;
    }
    else
    {

        PERR("non-existent date completion set attempted. Setting current year completion as default");
        dateCompletion = QOF_DATE_COMPLETION_THISYEAR;
    }

    if (backmonths < 0)
    {
        backmonths = 0;
    }
    else if (backmonths > 11)
    {
        backmonths = 11;
    }
    dateCompletionBackMonths = backmonths;

    return;
}
