dispose (GObject *object)
{
  ExampleCallContent *self = EXAMPLE_CALL_CONTENT (object);

  g_clear_object (&self->priv->stream);

  ((GObjectClass *) example_call_content_parent_class)->dispose (object);
}
