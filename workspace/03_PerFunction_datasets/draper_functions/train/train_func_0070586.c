draw_chart (CutCairoPieChart *chart, cairo_t *cr, CutRunContext *run_context)
{
    CutCairoPieChartPrivate *priv;
    GList *node;
    gdouble sum;
    gdouble start;

    priv = CUT_CAIRO_PIE_CHART_GET_PRIVATE(chart);

    cairo_set_line_width(cr, 0.75);

    sum = calculate_sum(chart, run_context);
    start = 2 * M_PI * 0.75;

    for (node = priv->series; node; node = g_list_next(node)) {
        CutTestResultStatus status;
        gint n_results;
        gdouble ratio;

        status = GPOINTER_TO_INT(node->data);
        cut_cairo_set_source_result_color(cr, status);
        n_results = get_status_result_number(run_context, status);
        if (n_results == 0)
            continue;

        ratio = (gdouble)n_results / (gdouble)sum;
        start = draw_pie_piece(chart, cr, start, ratio);
    }
}
