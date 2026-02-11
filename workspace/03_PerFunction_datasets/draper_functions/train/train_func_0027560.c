clutter_event_get_device (const ClutterEvent *event)
{
  ClutterInputDevice *device = NULL;

  g_return_val_if_fail (event != NULL, NULL);

  if (is_event_allocated (event))
    {
      ClutterEventPrivate *real_event = (ClutterEventPrivate *) event;

      if (real_event->device != NULL)
        return real_event->device;
    }

  switch (event->type)
    {
    case CLUTTER_NOTHING:
    case CLUTTER_STAGE_STATE:
    case CLUTTER_DESTROY_NOTIFY:
    case CLUTTER_CLIENT_MESSAGE:
    case CLUTTER_DELETE:
    case CLUTTER_EVENT_LAST:
      break;

    case CLUTTER_ENTER:
    case CLUTTER_LEAVE:
      device = event->crossing.device;
      break;

    case CLUTTER_BUTTON_PRESS:
    case CLUTTER_BUTTON_RELEASE:
      device = event->button.device;
      break;

    case CLUTTER_MOTION:
      device = event->motion.device;
      break;

    case CLUTTER_SCROLL:
      device = event->scroll.device;
      break;

    case CLUTTER_TOUCH_BEGIN:
    case CLUTTER_TOUCH_UPDATE:
    case CLUTTER_TOUCH_END:
    case CLUTTER_TOUCH_CANCEL:
      device = event->touch.device;
      break;

    case CLUTTER_KEY_PRESS:
    case CLUTTER_KEY_RELEASE:
      device = event->key.device;
      break;
    }

  return device;
}
