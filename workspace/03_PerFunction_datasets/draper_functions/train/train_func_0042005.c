drawing_clear_selection(gpaint_drawing *drawing, gpaint_point_array *points)
{
   GdkGCValues gcvalues;
   GdkRectangle clientrect;

   if (point_array_size(points) > 2)
   {
      clientrect.x = clientrect.y = 0;
      clientrect.width  = drawing->width;
      clientrect.height = drawing->height;

      gdk_gc_get_values(drawing->gc, &gcvalues);
      gdk_gc_set_clip_origin(drawing->gc, 0, 0);
      gdk_gc_set_clip_rectangle(drawing->gc, &clientrect);

      gdk_gc_set_foreground(drawing->gc, &(gcvalues.background));

      gdk_draw_polygon(
              drawing->backing_pixmap,
              drawing->gc,
              TRUE,
              point_array_data(points),
              point_array_size(points));
      gdk_draw_polygon(
              drawing->window,
              drawing->gc,
              TRUE,
              point_array_data(points),
              point_array_size(points));

      gdk_gc_set_foreground(drawing->gc, &(gcvalues.foreground));
   }
}
