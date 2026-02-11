on_widget_button_press (GtkWidget *widget,
			GdkEventButton *event,
			char *item_id)
{
  GdkDevice *device = gdk_event_get_device ((GdkEvent*) event);

  g_print ("%s received 'button-press' signal\n", item_id);

  if (device && strstr (item_id, "explicit"))
    {
      GdkGrabStatus status;
      GdkEventMask mask = GDK_BUTTON_PRESS_MASK
	| GDK_BUTTON_RELEASE_MASK
	| GDK_POINTER_MOTION_MASK
	| GDK_POINTER_MOTION_HINT_MASK
	| GDK_ENTER_NOTIFY_MASK
	| GDK_LEAVE_NOTIFY_MASK;

      status = gdk_device_grab (device, gtk_widget_get_window (widget),
				GDK_OWNERSHIP_NONE, FALSE, mask,
				NULL, event->time);
      if (status == GDK_GRAB_SUCCESS)
	g_print ("grabbed pointer\n");
      else
	g_print ("pointer grab failed\n");
    }

  return TRUE;
}
