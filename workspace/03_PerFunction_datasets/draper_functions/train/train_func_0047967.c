_clutter_actor_get_transform_info_or_defaults (ClutterActor *self)
{
  ClutterTransformInfo *info;

  info = g_object_get_qdata (G_OBJECT (self), quark_actor_transform_info);
  if (info != NULL)
    return info;

  return &default_transform_info;
}
