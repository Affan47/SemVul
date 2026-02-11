clutter_actor_get_shader (ClutterActor *self)
{
  ShaderData *shader_data;

  g_return_val_if_fail (CLUTTER_IS_ACTOR (self), NULL);

  shader_data = g_object_get_data (G_OBJECT (self), "-clutter-actor-shader-data");
  if (shader_data != NULL)
    return shader_data->shader;

  return NULL;
}
