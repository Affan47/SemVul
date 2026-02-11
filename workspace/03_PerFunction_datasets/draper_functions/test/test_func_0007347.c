gc_drag_event (GooCanvasItem *item,
	       GooCanvasItem *target,
	       GdkEventButton *event,
	       gpointer data)
{
  switch(event->type)
    {
    case GDK_BUTTON_PRESS:
      if(gc_drag_status == 0 && event->button == 1)
	{
	  gc_drag_item = item;
	  gc_drag_target = target;
	  if(gc_drag_mode == GC_DRAG_MODE_GRAB)
	    gc_drag_status = 2;
	  else
	    gc_drag_status = 1;

	  gc_drag_user_data = data;
	  gc_drag_func(item, target, (GdkEvent*)event, data);
	}
      break;
    case GDK_BUTTON_RELEASE:
      if(gc_drag_status == 2)
	{
	  gc_drag_func(gc_drag_item,
		       item,
		       (GdkEvent*)event,
		       data);
	  gc_drag_status = 0;
	  gc_drag_item = NULL;
	  gc_drag_target = NULL;
	  gc_drag_user_data = NULL;
	}
      else if (gc_drag_status == 1 && gc_drag_mode & GC_DRAG_MODE_2CLICKS)
	gc_drag_status = 2;
      break;
    default:
      break;
    }
  return FALSE;
}
