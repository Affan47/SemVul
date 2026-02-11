draw_it(client_data, id)
XtPointer client_data;
XtIntervalId *id;
{
   StripChartWidget w = (StripChartWidget)client_data;
   double value;

   if (w->strip_chart.update > 0)
       w->strip_chart.interval_id =
       XtAppAddTimeOut(XtWidgetToApplicationContext( (Widget) w),
		       w->strip_chart.update * MS_PER_SEC,draw_it,client_data);

   if (w->strip_chart.interval >= (int)w->core.width)
       MoveChart( (StripChartWidget) w, TRUE);


   if (w->strip_chart.get_value == NULL)
       return;

   XtCallCallbacks( (Widget)w, XtNgetValue, (XtPointer)&value );


   if (value > w->strip_chart.max_value) {
       w->strip_chart.max_value = value;
       if (w->strip_chart.max_value > w->strip_chart.scale) {
	   XClearWindow( XtDisplay (w), XtWindow (w));
	   w->strip_chart.interval = repaint_window(w, 0, (int) w->core.width);
       }
   }

   w->strip_chart.valuedata[w->strip_chart.interval] = value;
   if (XtIsRealized((Widget)w)) {
       int y = (int) (w->core.height
		      - (int)(w->core.height * value) / w->strip_chart.scale);

       XFillRectangle(XtDisplay(w), XtWindow(w), w->strip_chart.fgGC,
		      w->strip_chart.interval, y,
		      (unsigned int) 1, w->core.height - y);


       if (w->strip_chart.points != NULL) {
	   w->strip_chart.points[0].x = w->strip_chart.interval;
	   XDrawPoints(XtDisplay(w), XtWindow(w), w->strip_chart.hiGC,
		       w->strip_chart.points, w->strip_chart.scale - 1,
		       CoordModePrevious);
       }

       XFlush(XtDisplay(w));
   }
   w->strip_chart.interval++;
}
