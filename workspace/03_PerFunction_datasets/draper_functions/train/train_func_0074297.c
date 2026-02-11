clutter_path_constraint_new (ClutterPath *path,
                             gfloat       offset)
{
  g_return_val_if_fail (path == NULL || CLUTTER_IS_PATH (path), NULL);

  return g_object_new (CLUTTER_TYPE_PATH_CONSTRAINT,
                       "path", path,
                       "offset", offset,
                       NULL);
}
