clutter_texture_set_cogl_material (ClutterTexture *texture,
                                   CoglHandle cogl_material)
{
  CoglPipeline *cogl_pipeline = cogl_material;
  CoglHandle cogl_texture;

  g_return_if_fail (CLUTTER_IS_TEXTURE (texture));

  cogl_object_ref (cogl_pipeline);

  if (texture->priv->pipeline)
    cogl_object_unref (texture->priv->pipeline);

  texture->priv->pipeline = cogl_pipeline;


  cogl_texture = clutter_texture_get_cogl_texture (texture);
  clutter_texture_set_cogl_texture (texture, cogl_texture);


}
