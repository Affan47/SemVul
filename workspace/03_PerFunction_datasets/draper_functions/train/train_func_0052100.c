gegl_color_new (const gchar *string)
{
  if (string)
    return g_object_new (GEGL_TYPE_COLOR, "string", string, NULL);

  return g_object_new (GEGL_TYPE_COLOR, NULL);
}
