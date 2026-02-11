Initialize (greq, gnew)
    Widget greq, gnew;
{
    StripChartWidget w = (StripChartWidget)gnew;

    if (w->strip_chart.update > 0)
        w->strip_chart.interval_id = XtAppAddTimeOut(
					XtWidgetToApplicationContext(gnew),
					w->strip_chart.update * MS_PER_SEC,
					draw_it, (XtPointer) gnew);
    CreateGC(w, (unsigned int) ALL_GCS);

    w->strip_chart.scale = w->strip_chart.min_scale;
    w->strip_chart.interval = 0;
    w->strip_chart.max_value = 0.0;
    w->strip_chart.points = NULL;
    SetPoints(w);
}
