poppler_attachment_dispose (GObject *obj)
{
  PopplerAttachmentPrivate *priv;

  priv = POPPLER_ATTACHMENT_GET_PRIVATE (obj);

  if (priv->obj_stream)
    {
      priv->obj_stream->free();
      delete priv->obj_stream;
      priv->obj_stream = NULL;
    }

  G_OBJECT_CLASS (poppler_attachment_parent_class)->dispose (obj);
}
