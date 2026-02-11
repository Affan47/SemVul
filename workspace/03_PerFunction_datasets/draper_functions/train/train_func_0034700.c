mx_entry_map (ClutterActor *actor)
{
  MxEntryPrivate *priv = MX_ENTRY (actor)->priv;

  CLUTTER_ACTOR_CLASS (mx_entry_parent_class)->map (actor);

  clutter_actor_map (priv->entry);

  if (priv->primary_icon)
    clutter_actor_map (priv->primary_icon);

  if (priv->primary_icon_highlight)
    clutter_actor_map (priv->primary_icon_highlight);

  if (priv->secondary_icon)
    clutter_actor_map (priv->secondary_icon);

  if (priv->secondary_icon_highlight)
    clutter_actor_map (priv->secondary_icon_highlight);

  if (priv->secondary_icon_tooltip)
    clutter_actor_map (CLUTTER_ACTOR (priv->secondary_icon_tooltip));

  if (priv->primary_icon_tooltip)
    clutter_actor_map (CLUTTER_ACTOR (priv->primary_icon_tooltip));
}
