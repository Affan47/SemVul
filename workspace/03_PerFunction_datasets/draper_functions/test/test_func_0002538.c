draggable_rectangle_parent_set (ClutterActor *actor,
                                ClutterActor *old_parent)
{
  ClutterActor *new_parent = clutter_actor_get_parent (actor);

  g_debug ("%s: old_parent: %s, new_parent: %s (%s)",
           G_STRLOC,
           old_parent ? G_OBJECT_TYPE_NAME (old_parent) : "none",
           new_parent ? clutter_actor_get_name (new_parent) : "Unknown",
           new_parent ? G_OBJECT_TYPE_NAME (new_parent) : "none");
}
