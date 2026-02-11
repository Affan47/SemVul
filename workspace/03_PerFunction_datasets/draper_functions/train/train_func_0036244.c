fit_param_row_update_value(FitControls *controls,
                           gint i,
                           gboolean errorknown)
{
    FitParamControl *cntrl;
    FitParamArg *arg;
    GwySIValueFormat *vf;
    GwySIUnit *unitx, *unity, *unitp;
    char buf[16];

    cntrl = &g_array_index(controls->param, FitParamControl, i);
    arg = &g_array_index(controls->args->param, FitParamArg, i);

    if (!controls->args->fitter->eval) {
        gtk_label_set_text(GTK_LABEL(cntrl->value), "");
        gtk_label_set_text(GTK_LABEL(cntrl->value_unit), "");
        gtk_label_set_text(GTK_LABEL(cntrl->error), "");
        gtk_label_set_text(GTK_LABEL(cntrl->error_unit), "");
        return;
    }

    g_object_get(controls->args->graph_model,
                 "si-unit-x", &unitx,
                 "si-unit-y", &unity,
                 NULL);
    unitp = gwy_nlfit_preset_get_param_units(controls->args->fitfunc, i,
                                             unitx, unity);
    g_object_unref(unitx);
    g_object_unref(unity);
    vf = gwy_si_unit_get_format_with_digits(unitp, GWY_SI_UNIT_FORMAT_VFMARKUP,
                                            arg->value, 4, NULL);

    g_snprintf(buf, sizeof(buf), "%.*f",
               vf->precision, arg->value/vf->magnitude);
    fix_minus(buf, sizeof(buf));
    gtk_label_set_text(GTK_LABEL(cntrl->value), buf);
    gtk_label_set_markup(GTK_LABEL(cntrl->value_unit), vf->units);

    if (!errorknown) {
        gtk_label_set_text(GTK_LABEL(cntrl->error), "");
        gtk_label_set_text(GTK_LABEL(cntrl->error_unit), "");
        gwy_si_unit_value_format_free(vf);
        return;
    }

    vf = gwy_si_unit_get_format_with_digits(unitp, GWY_SI_UNIT_FORMAT_VFMARKUP,
                                            arg->error, 1, vf);
    g_snprintf(buf, sizeof(buf), "%.*f",
               vf->precision, arg->error/vf->magnitude);
    gtk_label_set_text(GTK_LABEL(cntrl->error), buf);
    gtk_label_set_markup(GTK_LABEL(cntrl->error_unit), vf->units);

    gwy_si_unit_value_format_free(vf);
}
