normalize_data(FitArgs *args)
{
    gint i, j, ns;
    gboolean skip_first_point = FALSE;
    GwyGraphCurveModel *cmodel;
    const gdouble *xs, *ys;
    const gchar *func_name;
    gdouble *xd, *yd;

    cmodel = gwy_graph_model_get_curve(args->graph_model, 0);
    xs = gwy_graph_curve_model_get_xdata(cmodel);
    ys = gwy_graph_curve_model_get_ydata(cmodel);
    ns = gwy_graph_curve_model_get_ndata(cmodel);
    args->cdata = gwy_graph_curve_model_get_calibration_data(cmodel);

    gwy_data_line_resample(args->xdata, ns, GWY_INTERPOLATION_NONE);
    gwy_data_line_resample(args->ydata, ns, GWY_INTERPOLATION_NONE);
    xd = gwy_data_line_get_data(args->xdata);
    yd = gwy_data_line_get_data(args->ydata);


    func_name = gwy_resource_get_name(GWY_RESOURCE(args->fitfunc));
    if (gwy_strequal(func_name, "Gaussian (PSDF)")
        || gwy_strequal(func_name, "Power"))
        skip_first_point = TRUE;

    j = 0;
    for (i = 0; i < ns; i++) {
        if (((args->from == args->to)
             || (xs[i] >= args->from && xs[i] <= args->to))
            && !(skip_first_point && i == 0)) {

            xd[j] = xs[i];
            yd[j] = ys[i];
            j++;
        }
    }
    if (j == 0)
        return 0;

    if (j < ns) {
        gwy_data_line_resize(args->xdata, 0, j);
        gwy_data_line_resize(args->ydata, 0, j);
    }

    return j;
}
