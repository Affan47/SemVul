gwy_graph_model_curve_notify(GwyGraphCurveModel *cmodel,
                             GParamSpec *pspec,
                             GwyGraphModel *gmodel)
{
    gint i;


    i = gwy_graph_model_get_curve_index(gmodel, cmodel);
    g_return_if_fail(i > -1);
    g_signal_emit(gmodel, graph_model_signals[CURVE_NOTIFY], 0, i, pspec);
}
