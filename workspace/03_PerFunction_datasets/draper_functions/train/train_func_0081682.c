cally_text_get_caret_offset (AtkText *text)
{
  ClutterActor *actor        = NULL;

  actor = CALLY_GET_CLUTTER_ACTOR (text);
  if (actor == NULL)
    return -1;

  return clutter_text_get_cursor_position (CLUTTER_TEXT (actor));
}
