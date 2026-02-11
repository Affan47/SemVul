cut_test_context_push_backtrace (CutTestContext *context,
                                 const char     *relative_path,
                                 const char     *filename,
                                 unsigned int    line,
                                 const char     *function_name,
                                 const char     *info)
{
    CutTestContextPrivate *priv;
    CutBacktraceEntry *entry;
    gchar *full_filename = NULL;

    g_return_if_fail(context != NULL);
    g_return_if_fail(CUT_IS_TEST_CONTEXT(context));

    priv = CUT_TEST_CONTEXT_GET_PRIVATE(context);

    g_mutex_lock(priv->mutex);
    if (relative_path) {
        const gchar *source_directory = NULL;
        gchar *convert_relative_path;

        convert_relative_path =
            convert_directory_separator_in_relative_path(relative_path);

        if (priv->run_context)
            source_directory =
                cut_run_context_get_source_directory(priv->run_context);
        if (source_directory)
            full_filename = g_build_filename(source_directory,
                                             convert_relative_path,
                                             filename,
                                             NULL);
        else
            full_filename = g_build_filename(convert_relative_path,
                                             filename, NULL);
        g_free(convert_relative_path);
    } else {
        full_filename = cut_test_context_build_source_filename(context,
                                                               filename);
    }
    entry = cut_backtrace_entry_new(full_filename, line, function_name, info);
    g_free(full_filename);
    priv->backtrace = g_list_prepend(priv->backtrace, entry);
    g_mutex_unlock(priv->mutex);
}
