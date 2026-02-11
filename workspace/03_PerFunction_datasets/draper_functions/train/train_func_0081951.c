clutter_texture_set_pick_with_alpha (ClutterTexture *texture,
                                     gboolean        pick_with_alpha)
{
  ClutterTexturePrivate *priv;

  g_return_if_fail (CLUTTER_IS_TEXTURE (texture));

  priv = texture->priv;

  if (priv->pick_with_alpha == pick_with_alpha)
    return;

  if (!pick_with_alpha && priv->pick_pipeline != NULL)
    {
      cogl_object_unref (priv->pick_pipeline);
      priv->pick_pipeline = NULL;
    }


  priv->pick_with_alpha = pick_with_alpha;


  clutter_actor_queue_redraw (CLUTTER_ACTOR (texture));
}
