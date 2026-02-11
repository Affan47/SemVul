key_press_cb (ClutterActor *actor, ClutterEvent *event, gpointer data)
{
  hide_cursor ();

  if (!(event->type == CLUTTER_KEY_PRESS))
    return FALSE;

  return gnibbles_keypress_worms (event->key.keyval);
}
