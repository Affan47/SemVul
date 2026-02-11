goo_canvas_set_scale_internal	(GooCanvas *canvas,
				 gdouble    scale_x,
				 gdouble    scale_y)
{
  gdouble x, y;

  g_return_if_fail (GOO_IS_CANVAS (canvas));


  x = gtk_adjustment_get_value (canvas->hadjustment) + gtk_adjustment_get_page_size (canvas->hadjustment)/ 2;
  y = gtk_adjustment_get_value (canvas->vadjustment) + gtk_adjustment_get_page_size (canvas->vadjustment)/ 2;


  goo_canvas_convert_from_pixels (canvas, &x, &y);


#if 0
  if (gtk_widget_get_mapped (GTK_WIDGET (canvas)))
    gdk_window_show (canvas->tmp_window);
#endif

  canvas->freeze_count++;

  canvas->scale_x = scale_x;
  canvas->scale_y = scale_y;
  canvas->scale = MIN (scale_x, scale_y);
  reconfigure_canvas (canvas, FALSE);


  x -= gtk_adjustment_get_page_size (canvas->hadjustment)/ canvas->device_to_pixels_x / 2;
  y -= gtk_adjustment_get_page_size (canvas->vadjustment)/ canvas->device_to_pixels_y / 2;


  goo_canvas_scroll_to (canvas, x, y);

  canvas->freeze_count--;
  goo_canvas_adjustment_value_changed (NULL, canvas);


#if 0
  if (gtk_widget_get_mapped (GTK_WIDGET (canvas)))
    gdk_window_hide (canvas->tmp_window);
#endif
  gtk_widget_queue_draw (GTK_WIDGET (canvas));
}
