test_gnc_date_dateformat_to_string (void)
{
    g_assert_cmpstr (gnc_date_dateformat_to_string (QOF_DATE_FORMAT_US), ==, "us");
    g_assert_cmpstr (gnc_date_dateformat_to_string (QOF_DATE_FORMAT_UK), ==, "uk");
    g_assert_cmpstr (gnc_date_dateformat_to_string (QOF_DATE_FORMAT_CE), ==, "ce");
    g_assert_cmpstr (gnc_date_dateformat_to_string (QOF_DATE_FORMAT_ISO), ==, "iso");
    g_assert_cmpstr (gnc_date_dateformat_to_string (QOF_DATE_FORMAT_UTC), ==, "utc");
    g_assert_cmpstr (gnc_date_dateformat_to_string (QOF_DATE_FORMAT_LOCALE), ==, "locale");
    g_assert_cmpstr (gnc_date_dateformat_to_string (QOF_DATE_FORMAT_CUSTOM), ==, "custom");

}
