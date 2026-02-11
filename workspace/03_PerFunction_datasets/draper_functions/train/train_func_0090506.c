on_drawingarea_warped_expose_event     (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
  GdkPixmap *pixmap;

  int i=    GPOINTER_TO_UINT(gtk_widget_get_data_top(widget,"imagenum"));
  if(i>0)
    pixmap=sp->im_warped_pixmap[i];
  else
    pixmap=gtk_widget_get_data_top(widget,"pixmap");


  g_return_val_if_fail(pixmap,FALSE);


  gdk_gc_set_clip_rectangle (widget->style->fg_gc[widget->state],
			       &event->area);
  gdk_draw_pixmap(widget->window,
		  widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
		  pixmap,
		  event->area.x, event->area.y,
		  event->area.x, event->area.y,
		  event->area.width, event->area.height);

  gdk_gc_set_clip_rectangle (widget->style->fg_gc[widget->state],
			     NULL);
  return TRUE;
}
