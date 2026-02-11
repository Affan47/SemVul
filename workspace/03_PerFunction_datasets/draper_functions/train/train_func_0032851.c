mx_focus_manager_event_cb (ClutterStage   *stage,
                           ClutterEvent   *event,
                           MxFocusManager *manager)
{
  MxFocusable *old_focus;
  MxFocusManagerPrivate *priv = manager->priv;

  if (event->type != CLUTTER_KEY_PRESS)
    return FALSE;

  old_focus = priv->focused;
  switch (event->key.keyval)
    {
    case CLUTTER_KEY_Tab:
    case CLUTTER_KEY_ISO_Left_Tab:
      if (event->key.modifier_state & CLUTTER_SHIFT_MASK)
        mx_focus_manager_move_focus (manager, MX_FOCUS_DIRECTION_PREVIOUS);
      else
        mx_focus_manager_move_focus (manager, MX_FOCUS_DIRECTION_NEXT);
      break;

    case CLUTTER_KEY_Right:
      mx_focus_manager_move_focus (manager, MX_FOCUS_DIRECTION_RIGHT);
      break;

    case CLUTTER_KEY_Left:
      mx_focus_manager_move_focus (manager, MX_FOCUS_DIRECTION_LEFT);
      break;

    case CLUTTER_KEY_Up:
      mx_focus_manager_move_focus (manager, MX_FOCUS_DIRECTION_UP);
      break;

    case CLUTTER_KEY_Down:
      mx_focus_manager_move_focus (manager, MX_FOCUS_DIRECTION_DOWN);
      break;

    default:
      return FALSE;
    }

  if (priv->focused == old_focus)
    return FALSE;
  else
    return TRUE;
}
