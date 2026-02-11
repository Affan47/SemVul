emit_pointer_event (GooCanvas *canvas,
		    gchar     *signal_name,
		    GdkEvent  *original_event)
{
  GdkEvent event = *original_event;
  GooCanvasItem *target_item = canvas->pointer_item;
  double *x, *y, *x_root, *y_root;


  if (canvas->pointer_grab_item)
    {


      if ((event.type == GDK_ENTER_NOTIFY || event.type == GDK_LEAVE_NOTIFY)
	  && canvas->pointer_item != canvas->pointer_grab_item)
	return FALSE;

      target_item = canvas->pointer_grab_item;
    }


  if (target_item && !ITEM_IS_VALID (target_item))
    return FALSE;


  switch (event.type)
    {
    case GDK_MOTION_NOTIFY:
      x = &event.motion.x;
      y = &event.motion.y;
      x_root = &event.motion.x_root;
      y_root = &event.motion.y_root;
      break;
    case GDK_ENTER_NOTIFY:
    case GDK_LEAVE_NOTIFY:
      x = &event.crossing.x;
      y = &event.crossing.y;
      x_root = &event.crossing.x_root;
      y_root = &event.crossing.y_root;
      break;
    case GDK_SCROLL:
      x = &event.scroll.x;
      y = &event.scroll.y;
      x_root = &event.scroll.x_root;
      y_root = &event.scroll.y_root;
      break;
    default:

      x = &event.button.x;
      y = &event.button.y;
      x_root = &event.button.x_root;
      y_root = &event.button.y_root;
      break;
    }


  *x += 0.5;
  *y += 0.5;


  goo_canvas_convert_from_pixels (canvas, x, y);


  if (target_item && goo_canvas_item_get_is_static (target_item))
    goo_canvas_convert_to_static_item_space (canvas, x, y);


  *x_root = *x;
  *y_root = *y;


  goo_canvas_convert_to_item_space (canvas, target_item, x, y);

  return propagate_event (canvas, target_item, signal_name, &event);
}
