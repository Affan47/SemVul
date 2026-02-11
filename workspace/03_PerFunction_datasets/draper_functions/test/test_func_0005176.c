test_options_from_ibus_layout (void)
{
        gint i, j;
        gchar *output_0[] = {
                NULL
        };
        gchar *output_1[] = {
                "",
                NULL
        };
        gchar *output_2[] = {
                "b",
                NULL
        };
        gchar *output_3[] = {
                "b", "",
                NULL
        };
        gchar *output_4[] = {
                "b", "c",
                NULL
        };
        const gpointer tests[][2] = {

                { "",                   NULL },
                { "a",                  NULL },
                { "a[",                 output_0 },
                { "a[]",                output_1 },
                { "a[b]",               output_2 },
                { "a[b,]",              output_3 },
                { "a[b,c]",             output_4 },
        };

        for (i = 0; i < G_N_ELEMENTS (tests); ++i) {
                if (tests[i][1] == NULL) {
                        g_assert (options_from_ibus_layout (tests[i][0]) == NULL);
                } else {
                        gchar **strv_a = options_from_ibus_layout (tests[i][0]);
                        gchar **strv_b = tests[i][1];

                        g_assert (g_strv_length (strv_a) == g_strv_length (strv_b));
                        for (j = 0; j < g_strv_length (strv_a); ++j)
                                g_assert_cmpstr (strv_a[j], ==, strv_b[j]);
                }
        }
}
