clutter_actor_store_content_box (ClutterActor *self,
                                 const ClutterActorBox *box)
{
  if (box != NULL)
    {
      self->priv->content_box = *box;
      self->priv->content_box_valid = TRUE;
    }
  else
    self->priv->content_box_valid = FALSE;

  clutter_actor_queue_redraw (self);

  g_object_notify_by_pspec (G_OBJECT (self), obj_props[PROP_CONTENT_BOX]);
}
