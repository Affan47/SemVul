clutter_texture_get_cogl_texture (ClutterTexture *texture)
{
  ClutterTexturePrivate *priv;
  int layer_index;

  g_return_val_if_fail (CLUTTER_IS_TEXTURE (texture), NULL);

  priv = texture->priv;

  if (get_first_layer_index (priv->pipeline, &layer_index))
    return cogl_pipeline_get_layer_texture (priv->pipeline, layer_index);
  else
    return NULL;
}
