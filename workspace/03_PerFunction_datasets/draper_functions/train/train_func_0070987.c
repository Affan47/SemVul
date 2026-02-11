on_stage_capture (ClutterActor *stage,
                  ClutterEvent *event,
                  DragContext  *context)
{
  switch (event->type)
    {
    case CLUTTER_MOTION:
      if (context->in_drag)
        {
          ClutterMotionEvent *mevent = (ClutterMotionEvent *) event;


          if (!(mevent->modifier_state & CLUTTER_BUTTON1_MASK))
            return draggable_release (context, (ClutterButtonEvent *) event);
          else
            return draggable_motion (context, (ClutterMotionEvent *) event);
        }
      break;

    case CLUTTER_BUTTON_RELEASE:
      if (context->in_drag)
        return draggable_release (context, (ClutterButtonEvent *) event);
      break;

    default:
      break;
    }

  return FALSE;
}
