meta_frames_motion_notify_event     (GtkWidget           *widget,
                                     GdkEventMotion      *event)
{
  MetaUIFrame *frame;
  MetaFrames *frames;
  MetaGrabOp grab_op;
  Display *display;

  frames = META_FRAMES (widget);
  display = GDK_DISPLAY_XDISPLAY (gdk_window_get_display (event->window));

  frame = meta_frames_lookup_window (frames, GDK_WINDOW_XID (event->window));
  if (frame == NULL)
    return FALSE;

  frames->last_motion_frame = frame;

  grab_op = meta_core_get_grab_op (display);

  switch (grab_op)
    {
    case META_GRAB_OP_CLICKING_MENU:
    case META_GRAB_OP_CLICKING_DELETE:
    case META_GRAB_OP_CLICKING_MINIMIZE:
    case META_GRAB_OP_CLICKING_MAXIMIZE:
    case META_GRAB_OP_CLICKING_UNMAXIMIZE:
    case META_GRAB_OP_CLICKING_SHADE:
    case META_GRAB_OP_CLICKING_UNSHADE:
    case META_GRAB_OP_CLICKING_ABOVE:
    case META_GRAB_OP_CLICKING_UNABOVE:
    case META_GRAB_OP_CLICKING_STICK:
    case META_GRAB_OP_CLICKING_UNSTICK:
      {
        MetaFrameControl control;
        int x, y;

        gdk_window_get_device_position (frame->window, event->device,
                                        &x, &y, NULL);


        control = get_control (frames, frame, x, y);
        if (! ((control == META_FRAME_CONTROL_MENU &&
                grab_op == META_GRAB_OP_CLICKING_MENU) ||
               (control == META_FRAME_CONTROL_DELETE &&
                grab_op == META_GRAB_OP_CLICKING_DELETE) ||
               (control == META_FRAME_CONTROL_MINIMIZE &&
                grab_op == META_GRAB_OP_CLICKING_MINIMIZE) ||
               ((control == META_FRAME_CONTROL_MAXIMIZE ||
                 control == META_FRAME_CONTROL_UNMAXIMIZE) &&
                (grab_op == META_GRAB_OP_CLICKING_MAXIMIZE ||
                 grab_op == META_GRAB_OP_CLICKING_UNMAXIMIZE)) ||
               (control == META_FRAME_CONTROL_SHADE &&
                grab_op == META_GRAB_OP_CLICKING_SHADE) ||
               (control == META_FRAME_CONTROL_UNSHADE &&
                grab_op == META_GRAB_OP_CLICKING_UNSHADE) ||
               (control == META_FRAME_CONTROL_ABOVE &&
                grab_op == META_GRAB_OP_CLICKING_ABOVE) ||
               (control == META_FRAME_CONTROL_UNABOVE &&
                grab_op == META_GRAB_OP_CLICKING_UNABOVE) ||
               (control == META_FRAME_CONTROL_STICK &&
                grab_op == META_GRAB_OP_CLICKING_STICK) ||
               (control == META_FRAME_CONTROL_UNSTICK &&
                grab_op == META_GRAB_OP_CLICKING_UNSTICK)))
           control = META_FRAME_CONTROL_NONE;


        meta_frames_update_prelit_control (frames, frame, control);
      }
      break;
    case META_GRAB_OP_NONE:
      {
        MetaFrameControl control;
        int x, y;

        gdk_window_get_device_position (frame->window, event->device,
                                        &x, &y, NULL);

        control = get_control (frames, frame, x, y);


        meta_frames_update_prelit_control (frames, frame, control);
      }
      break;

    default:
      break;
    }

  return TRUE;
}
