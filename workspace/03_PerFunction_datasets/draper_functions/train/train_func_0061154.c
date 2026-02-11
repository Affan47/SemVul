webx_preview_area_realize (GtkWidget       *widget,
                           WebxPreview     *preview)
{
  if (! preview->area_gc)
    {
      preview->area_gc = gdk_gc_new (widget->window);
    }
}
