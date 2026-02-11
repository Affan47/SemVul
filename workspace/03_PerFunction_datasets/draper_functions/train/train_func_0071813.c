print_results (CutConsoleUI *console, CutRunContext *run_context)
{
    gint i;
    const GList *node;

    i = 1;
    for (node = console->errors; node; node = g_list_next(node)) {
        GError *error = node->data;

        g_print("\n%d) ", i);
        print_for_status(console, CUT_TEST_RESULT_ERROR,
                         "SystemError: %s:%d",
                         g_quark_to_string(error->domain),
                         error->code);
        if (error->message) {
            g_print("\n");
            print_for_status(console, CUT_TEST_RESULT_ERROR,
                             "%s", error->message);
        }
        g_print("\n");
        i++;
    }

    for (node = cut_run_context_get_results(run_context);
         node;
         node = g_list_next(node)) {
        CutTestResult *result = node->data;
        CutTestResultStatus status;
        CutTest *test;
        const GList *node;
        const gchar *name;

        status = cut_test_result_get_status(result);
        if (status == CUT_TEST_RESULT_SUCCESS)
            continue;

        name = cut_test_result_get_test_name(result);
        if (!name)
            name = cut_test_result_get_test_case_name(result);
        if (!name)
            name = cut_test_result_get_test_suite_name(result);

        g_print("\n%d) ", i);
        print_for_status(console, status, "%s", status_to_label(status));
        g_print(": %s", name);

        test = cut_test_result_get_test(result);
        if (test)
            print_test_attributes(console, status, test);

        print_result_detail(console, status, result);

        g_print("\n");
        for (node = cut_test_result_get_backtrace(result);
             node;
             node = g_list_next(node)) {
            CutBacktraceEntry *entry = node->data;
            gchar *formatted_entry;

            formatted_entry = cut_backtrace_entry_format(entry);
            g_print("%s\n", formatted_entry);
            g_free(formatted_entry);
        }
        i++;
    }
}
