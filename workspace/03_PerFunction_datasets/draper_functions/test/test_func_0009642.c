json_reader_set_root (JsonReader *reader,
                      JsonNode   *root)
{
  JsonReaderPrivate *priv;

  g_return_if_fail (JSON_IS_READER (reader));

  priv = reader->priv;

  if (priv->root == root)
    return;

  if (priv->root != NULL)
    {
      json_node_free (priv->root);
      priv->root = NULL;
      priv->current_node = NULL;
      priv->previous_node = NULL;
    }

  if (root != NULL)
    {
      priv->root = json_node_copy (root);
      priv->current_node = priv->root;
      priv->previous_node = NULL;
    }

  g_object_notify_by_pspec (G_OBJECT (reader), reader_properties[PROP_ROOT]);
}
