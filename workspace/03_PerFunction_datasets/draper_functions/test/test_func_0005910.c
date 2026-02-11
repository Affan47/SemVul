mx_image_clear (MxImage *image)
{
  MxImagePrivate *priv = image->priv;

  mx_image_cancel_in_progress (image);

  if (priv->texture)
    cogl_object_unref (priv->texture);

  priv->texture = cogl_object_ref (priv->blank_texture);


  if (priv->old_texture)
    cogl_object_unref (priv->old_texture);

  priv->old_texture = cogl_object_ref (priv->blank_texture);
  priv->old_rotation = priv->rotation;
  priv->old_mode = priv->mode;


  if (priv->material)
    cogl_object_unref (priv->material);

  priv->material = cogl_object_ref (priv->template_material);


  clutter_actor_queue_relayout (CLUTTER_ACTOR (image));
}
