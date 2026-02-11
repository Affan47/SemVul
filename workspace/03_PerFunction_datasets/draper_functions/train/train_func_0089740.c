file_source_free (FileSource *self)
{
  g_return_if_fail (self != NULL);

  g_free (self->id);
  g_free (self->file_name);
  g_free (self->file_type);

  g_object_unref (self->peer);

  if (self->node != NULL)
    g_object_unref (self->node);

  g_slice_free (FileSource, self);
}
