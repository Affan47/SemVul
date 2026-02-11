_upload_complete_cb (RestProxyCall *call,
                     const GError  *error,
                     GObject       *weak_object,
                     gpointer       user_data)
{
  VimeoUploadCtx *ctx = (VimeoUploadCtx *) user_data;
  SwServiceVimeo *self = SW_SERVICE_VIMEO (weak_object);
  SwServiceVimeoPrivate *priv = self->priv;
  GError *err = NULL;
  RestXmlNode *root = node_from_call (call, &err);

  if (err != NULL) {
    UPLOAD_ERROR ("%s", err->message);
    g_error_free (err);
    goto OUT;
  }

  ctx->video_id = g_strdup (get_child_attribute (root, "ticket", "video_id"));

  SW_DEBUG (VIMEO, "Complete: %s", ctx->video_id);

  if (ctx->title != NULL)
    _simple_rest_async_run (priv->proxy, "api/rest/v2",
                            _set_title_cb, G_OBJECT (self), ctx, NULL,
                            "method", "vimeo.videos.setTitle",
                            "title", ctx->title,
                            "video_id", ctx->video_id,
                            NULL);
  else if (ctx->description != NULL)
    _simple_rest_async_run (priv->proxy, "api/rest/v2",
                            _set_description_cb, G_OBJECT (self), ctx, NULL,
                            "method", "vimeo.videos.setDescription",
                            "description", ctx->description,
                            "video_id", ctx->video_id,
                            NULL);
  else if (ctx->collection_id != NULL)
    _add_video_to_album (self, ctx);
  else
    _upload_completed (self, ctx);

 OUT:
  if (root != NULL)
    rest_xml_node_unref (root);
}
