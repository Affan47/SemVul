check_command_line_files(gint n,
                         gchar **args)
{
    gint i, nfailures;


    for (i = nfailures = 0; i < n; i++) {
        const gchar *filename = args[i];
        const gchar *name = NULL;
        GwyContainer *data;
        GError *error = NULL;
        GSList *failures, *f;

        if (!(data = gwy_file_load(filename, GWY_RUN_NONINTERACTIVE, &error))) {
            if (!error)
                g_printerr("%s: Loader failed to report error properly!\n",
                           filename);
            else {
                g_printerr("%s: %s\n", filename, error->message);
                g_clear_error(&error);
            }
            continue;
        }

        failures = gwy_data_validate(data, GWY_DATA_VALIDATE_ALL);
        gwy_file_get_data_info(data, &name, NULL);
        g_assert(name);
        for (f = failures; f; f = g_slist_next(f)) {
            GwyDataValidationFailure *failure;

            failure = (GwyDataValidationFailure*)f->data;
            g_printerr("%s: %s, %s: %s",
                       filename, name,
                       g_quark_to_string(failure->key),
                       gwy_data_error_desrcibe(failure->error));
            if (failure->details)
                g_printerr(" (%s)", failure->details);
            g_printerr("\n");

            nfailures++;
        }
        gwy_data_validation_failure_list_free(failures);
    }

    return nfailures;
}
