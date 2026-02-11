on_key_press (ClutterActor *stage,
              ClutterEvent *event,
              ClutterActor *box)
{
  guint keysym = clutter_event_get_key_symbol (event);
  MultiLayout *layout = (MultiLayout *) clutter_actor_get_layout_manager (box);

  if (keysym == CLUTTER_KEY_q)
    {
      clutter_main_quit ();
      return CLUTTER_EVENT_STOP;
    }

  switch (keysym)
    {
    case CLUTTER_KEY_g:
      multi_layout_set_state (layout, MULTI_LAYOUT_GRID);
      break;

    case CLUTTER_KEY_c:
      multi_layout_set_state (layout, MULTI_LAYOUT_CIRCLE);
      break;

    default:
      break;
    }

  return CLUTTER_EVENT_STOP;
}
