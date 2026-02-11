markdown_config_finalize(GObject *object)
{
  MarkdownConfig *self;

  g_return_if_fail(MARKDOWN_IS_CONFIG(object));

  self = MARKDOWN_CONFIG(object);

  if (self->priv->handle != 0) {
    g_source_remove(self->priv->handle);
    markdown_config_save(self);
  }

  g_free(self->priv->filename);
  g_key_file_free(self->priv->kf);

  G_OBJECT_CLASS(markdown_config_parent_class)->finalize (object);
}
