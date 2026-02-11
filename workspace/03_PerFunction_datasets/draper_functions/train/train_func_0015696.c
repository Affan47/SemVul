gwy_graph_area_find_curve(GwyGraphArea *area, gdouble x, gdouble y)
{
    gint i, j, nc, ndata;
    gint closestid = -1;
    gdouble closestdistance, distance = 0.0;
    const gdouble *xdata, *ydata;
    GwyGraphCurveModel *curvemodel;
    GwyGraphModel *model;

    closestdistance = G_MAXDOUBLE;
    model = area->graph_model;
    nc = gwy_graph_model_get_n_curves(model);
    for (i = 0; i < nc; i++) {
        curvemodel = gwy_graph_model_get_curve(model, i);
        ndata = gwy_graph_curve_model_get_ndata(curvemodel);
        xdata = gwy_graph_curve_model_get_xdata(curvemodel);
        ydata = gwy_graph_curve_model_get_ydata(curvemodel);
        for (j = 0; j < ndata - 1; j++) {
            if (xdata[j] <= x && xdata[j + 1] >= x) {
                distance = fabs(y - ydata[j]
                                + (x - xdata[j])*(ydata[j + 1] - ydata[j])
                                  /(xdata[j + 1] - xdata[j]));
                if (distance < closestdistance) {
                    closestdistance = distance;
                    closestid = i;
                }
                break;
            }
        }
    }
    if (fabs(closestdistance/(area->y_max - area->y_min)) < 0.05)
        return closestid;
    else
        return -1;
}
