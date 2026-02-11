grain_cross(GwyContainer *data, GwyRunType run)
{
    GwySIUnit *siunitxy, *siunitz;
    GrainCrossArgs args;
    GwyDataField *dfield;
    GwyDataField *mfield;
    gint id;

    g_return_if_fail(run & CROSS_RUN_MODES);
    grain_cross_load_args(gwy_app_settings_get(), &args);
    gwy_app_data_browser_get_current(GWY_APP_DATA_FIELD, &dfield,
                                     GWY_APP_DATA_FIELD_ID, &id,
                                     GWY_APP_MASK_FIELD, &mfield,
                                     0);
    g_return_if_fail(dfield && mfield);

    siunitxy = gwy_data_field_get_si_unit_xy(dfield);
    siunitz = gwy_data_field_get_si_unit_z(dfield);
    args.units_equal = gwy_si_unit_equal(siunitxy, siunitz);
    if (!args.units_equal) {
        GwyGrainValue *abscissa, *ordinate;

        abscissa = gwy_grain_values_get_grain_value(args.abscissa);
        ordinate = gwy_grain_values_get_grain_value(args.ordinate);
        if ((gwy_grain_value_get_flags(abscissa)
             | gwy_grain_value_get_flags(ordinate))
            & GWY_GRAIN_VALUE_SAME_UNITS) {
            GtkWidget *dialog;

            dialog = gtk_message_dialog_new
                                    (gwy_app_find_window_for_channel(data, id),
                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                     GTK_MESSAGE_ERROR,
                                     GTK_BUTTONS_OK,
                                     _("Grain correlation: Lateral dimensions "
                                       "and value must be the same physical "
                                       "quantity for the selected grain "
                                       "properties."));
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }
    }
    if (run == GWY_RUN_IMMEDIATE)
        grain_cross_run(&args, data, dfield, mfield);
    else {
        grain_cross_dialog(&args, data, dfield, mfield);
        grain_cross_save_args(gwy_app_settings_get(), &args);
    }
}
