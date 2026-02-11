champlain_label_new_full (const gchar *text,
    ClutterActor *actor)
{
  ChamplainLabel *label = CHAMPLAIN_LABEL (champlain_label_new ());

  if (actor != NULL)
    {
      champlain_label_set_image (label, actor);
    }
  champlain_label_set_text (label, text);

  return CLUTTER_ACTOR (label);
}
