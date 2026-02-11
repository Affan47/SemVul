infd_directory_add_note(InfdDirectory* directory,
                        InfdDirectoryIter* parent,
                        const gchar* name,
                        const InfdNotePlugin* plugin,
                        InfdDirectoryIter* iter,
                        GError** error)
{
  InfdDirectoryPrivate* priv;
  guint node_id;
  InfCommunicationHostedGroup* group;
  InfdDirectoryNode* node;

  g_return_val_if_fail(INFD_IS_DIRECTORY(directory), FALSE);
  g_return_val_if_fail(parent != NULL, FALSE);
  g_return_val_if_fail(name != NULL, FALSE);
  g_return_val_if_fail(plugin != NULL, FALSE);

  infd_directory_return_val_if_iter_fail(directory, parent, FALSE);
  infd_directory_return_val_if_subdir_fail(parent->node, FALSE);

  priv = INFD_DIRECTORY_PRIVATE(directory);

  if( ((InfdDirectoryNode*)parent->node)->shared.subdir.explored == FALSE)
    if(infd_directory_node_explore(directory, parent->node, error) == FALSE)
      return FALSE;

  node_id = priv->node_counter++;
  group = infd_directory_create_subscription_group(directory, node_id);

  node = infd_directory_node_create_new_note(
    directory,
    parent->node,
    group,
    node_id,
    name,
    plugin,
    error
  );

  g_object_unref(group);

  if(node == NULL)
    return FALSE;

  infd_directory_node_register(directory, node, NULL, NULL);

  if(iter != NULL)
  {
    iter->node = node;
    iter->node_id = node->id;
  }

  return TRUE;
}
