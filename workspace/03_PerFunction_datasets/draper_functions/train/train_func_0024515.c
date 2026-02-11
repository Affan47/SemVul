mx_stack_move_focus (MxFocusable      *focusable,
                    MxFocusDirection  direction,
                    MxFocusable      *from)
{
  GList *c;

  MxStackPrivate *priv = MX_STACK (focusable)->priv;

  if (direction == MX_FOCUS_DIRECTION_OUT)
    return NULL;

  focusable = NULL;

  c = g_list_find (priv->children, from);
  while (c && !focusable)
    {
      ClutterActor *child;

      switch (direction)
        {
        case MX_FOCUS_DIRECTION_PREVIOUS :
        case MX_FOCUS_DIRECTION_LEFT :
        case MX_FOCUS_DIRECTION_UP :
          c = c->prev;
          break;
        default:
          c = c->next;
          break;
        }

      if (!c)
        continue;

      child = c->data;
      if (!MX_IS_FOCUSABLE (child))
        continue;

      focusable = mx_focusable_accept_focus (MX_FOCUSABLE (child),
                                             MX_FOCUS_HINT_PRIOR);
      if (focusable)
        priv->current_focus = child;
    }

  return focusable;
}
