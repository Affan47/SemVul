fill_data(GwyGraphModel *gmodel,
          RawGraphArgs *args)
{
    GwyGraphCurveModel *gcmodel;
    GwySIUnit *unit;
    gint power10;
    guint i, j;
    gdouble q;

    unit = gwy_si_unit_new_parse(args->x_units, &power10);
    q = pow10(power10);

    for (j = 0; j < args->data->len; j++)
        args->xdata[j] = q*g_array_index(args->data, gdouble, j*args->ncols);

    gwy_si_unit_set_from_string_parse(unit, args->y_units, &power10);
    q = pow10(power10);

    for (i = 1; i < args->ncols; i++) {
        for (j = 0; j < args->data->len; j++)
            args->ydata[j] = q*g_array_index(args->data, gdouble,
                                             j*args->ncols + i);

        gcmodel = gwy_graph_model_get_curve(gmodel, i-1);
        gwy_graph_curve_model_set_data(gcmodel,
                                       args->xdata, args->ydata,
                                       args->data->len);
    }

    g_object_unref(unit);
}
