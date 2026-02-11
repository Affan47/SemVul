test_gnc_sql_convert_timespec_to_string ()
{
    GncSqlBackend be = {{
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
            0, NULL, 0, "", NULL, 0, "", NULL, NULL
        },
        NULL, NULL, FALSE, FALSE, FALSE, 0, 0, NULL,
        "%4d-%02d-%02d %02d:%02d:%02d"
    };
    gchar *date[numtests] = {"1995-03-11 19:17:26",
                             "2001-04-20 11:44:07",
                             "1964-02-29 09:15:23",
                             "1959-04-02 00:00:00",
                             "2043-11-22 05:32:45",
                             "2153-12-18 01:15:30"
                            };
    int i;
    for (i = 0; i < numtests; i++)
    {

        Timespec *ts = gnc_date_string_to_timespec_gmt (date[i]);
        gchar *datestr = gnc_sql_convert_timespec_to_string (&be, *ts);
        g_assert_cmpstr (date[i], ==, datestr);

        g_free (datestr);
        g_slice_free (Timespec, ts);
    }

}
