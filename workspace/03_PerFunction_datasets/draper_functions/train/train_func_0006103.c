test_gnc_date_string_to_dateformat (void)
{
    QofDateFormat fmt = 123;
    g_assert (gnc_date_string_to_dateformat (NULL, &fmt));
    g_assert_cmpint (fmt, ==, 123);
    g_assert (!gnc_date_string_to_dateformat ("us", &fmt));
    g_assert_cmpint (fmt, ==, QOF_DATE_FORMAT_US);
    g_assert (!gnc_date_string_to_dateformat ("uk", &fmt));
    g_assert_cmpint (fmt, ==, QOF_DATE_FORMAT_UK);
    g_assert (!gnc_date_string_to_dateformat ("ce", &fmt));
    g_assert_cmpint (fmt, ==, QOF_DATE_FORMAT_CE);
    g_assert (!gnc_date_string_to_dateformat ("iso", &fmt));
    g_assert_cmpint (fmt, ==, QOF_DATE_FORMAT_ISO);
    g_assert (!gnc_date_string_to_dateformat ("utc", &fmt));
    g_assert_cmpint (fmt, ==, QOF_DATE_FORMAT_UTC);
    g_assert (!gnc_date_string_to_dateformat ("locale", &fmt));
    g_assert_cmpint (fmt, ==, QOF_DATE_FORMAT_LOCALE);
    g_assert (!gnc_date_string_to_dateformat ("custom", &fmt));
    g_assert_cmpint (fmt, ==, QOF_DATE_FORMAT_CUSTOM);
    fmt = 123;
    g_assert (gnc_date_string_to_dateformat ("", &fmt));
    g_assert_cmpint (fmt, ==, 123);
    g_assert (gnc_date_string_to_dateformat ("foo", &fmt));
    g_assert_cmpint (fmt, ==, 123);

}
