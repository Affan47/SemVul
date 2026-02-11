gnb_stacked_bar_set_metric_color(
    GnbStackedBar *sbar,
    guint idx,
    const GdkColor *color)
{
    gboolean changed = FALSE;
    GnbStackedBarMetric *metric;

    g_return_if_fail(sbar != NULL);
    g_return_if_fail(GNB_IS_STACKED_BAR(sbar));
    g_return_if_fail(idx < sbar->nmetrics);

    metric = &sbar->metrics[idx];

    if (color != NULL)
    {
    	changed = !metric->color_set;
	metric->color_set = TRUE;
	metric->color = *color;
    }
    else
    {
    	changed = metric->color_set;
	metric->color_set = FALSE;

    }

    if (changed)
    {
    	if (metric->gc != NULL)
	{
	    gtk_gc_release(metric->gc);
	    metric->gc = NULL;
	}
	if (GTK_WIDGET_DRAWABLE(GTK_WIDGET(sbar)))
	    gtk_widget_queue_draw(GTK_WIDGET(sbar));
    }
}
