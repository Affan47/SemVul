detect_cpp_test_function_symbol_names_gcc (const gchar *name)
{
    const gchar *original_name = name;
    gchar *test_name_start;
    guint64 test_name_length;
    gchar *data_setup_function_name = NULL;
    gchar *attributes_setup_function_name = NULL;
    gboolean require_data_setup_function = FALSE;
    gchar *namespace;
    GString *test_name;

    test_name = g_string_new(NULL);
    if (!find_cpp_test_name_gcc(name, &test_name_start, &test_name_length,
                                test_name)) {
        g_string_free(test_name, TRUE);
        return NULL;
    }

    name = test_name_start + test_name_length;
    if (g_str_equal(name, "Ev")) {
    } else if (g_str_equal(name, "EPv") || g_str_equal(name, "EPKv")) {
        GString *data_setup_function_name_string;
        size_t test_name_prefix_length;

        require_data_setup_function = TRUE;

        test_name_prefix_length = strlen(TEST_NAME_PREFIX);

        data_setup_function_name_string = g_string_new(NULL);
        g_string_append_len(data_setup_function_name_string,
                            original_name, original_name - test_name_start);
        g_string_append(data_setup_function_name_string,
                        DATA_SETUP_FUNCTION_NAME_PREFIX);
        g_string_append_len(data_setup_function_name_string,
                            test_name_start + test_name_prefix_length,
                            test_name_length - test_name_prefix_length);
        g_string_append(data_setup_function_name_string, "Ev");

        data_setup_function_name = g_string_free(data_setup_function_name_string,
                                                 FALSE);
    } else {
        g_string_free(test_name, TRUE);
        return NULL;
    }

    {
        GString *attributes_setup_function_name_string;
        size_t test_name_prefix_length;

        test_name_prefix_length = strlen(TEST_NAME_PREFIX);

        attributes_setup_function_name_string = g_string_new(NULL);
        g_string_append_len(attributes_setup_function_name_string,
                            original_name, original_name - test_name_start);
        g_string_append(attributes_setup_function_name_string,
                        ATTRIBUTES_SETUP_FUNCTION_NAME_PREFIX);
        g_string_append_len(attributes_setup_function_name_string,
                            test_name_start + test_name_prefix_length,
                            test_name_length - test_name_prefix_length);
        g_string_append(attributes_setup_function_name_string, "Ev");

        attributes_setup_function_name =
            g_string_free(attributes_setup_function_name_string, FALSE);
    }

    if (test_name->len == 0) {
        namespace = g_strdup("");
    } else {
        namespace = g_strndup(test_name->str, test_name->len - 2);
    }
    g_string_append_len(test_name, test_name_start, test_name_length);
    return symbol_names_new(namespace,
                            g_string_free(test_name, FALSE),
                            g_strdup(original_name),
                            data_setup_function_name,
                            attributes_setup_function_name,
                            require_data_setup_function,
                            TRUE,
                            TRUE);
}
