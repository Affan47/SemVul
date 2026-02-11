gwy_data_validate(GwyContainer *data,
                  GwyDataValidateFlags flags)
{
    GwyDataValidationInfo info;
    GSList *errors;

    if ((flags & GWY_DATA_VALIDATE_NO_REPORT)
        && !(flags & GWY_DATA_VALIDATE_CORRECT)) {
        g_warning("Neither report no correction asked for, "
                  "validation is useless.");
        return NULL;
    }

    memset(&info, 0, sizeof(GwyDataValidationInfo));
    info.flags = flags;
    info.channels = g_array_new(FALSE, FALSE, sizeof(gint));
    info.graphs = g_array_new(FALSE, FALSE, sizeof(gint));
    info.spectra = g_array_new(FALSE, FALSE, sizeof(gint));
    info.volumes = g_array_new(FALSE, FALSE, sizeof(gint));

    gwy_container_foreach(data, NULL, &validate_item_pass1, &info);
    gwy_container_foreach(data, NULL, &validate_item_pass2, &info);
    if (flags & GWY_DATA_VALIDATE_REF_COUNT)
        gwy_container_foreach(data, NULL, &validate_item_pass3, &info);

    if (flags & GWY_DATA_VALIDATE_CORRECT)
        gwy_data_correct(data, info.errors);


    errors = g_slist_reverse(info.errors);

    g_array_free(info.channels, TRUE);
    g_array_free(info.graphs, TRUE);
    g_array_free(info.spectra, TRUE);
    g_array_free(info.volumes, TRUE);

    if (flags & GWY_DATA_VALIDATE_NO_REPORT) {
        gwy_data_validation_failure_list_free(errors);
        errors = NULL;
    }

    return errors;
}
