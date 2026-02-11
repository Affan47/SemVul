gfs_function_new_from_variable (GfsFunctionClass * klass,
					      GfsVariable * v)
{
  GfsFunction * object;

  g_return_val_if_fail (v != NULL, NULL);

  object = GFS_FUNCTION (gts_object_new (GTS_OBJECT_CLASS (klass)));
  object->v = v;

  return object;
}
