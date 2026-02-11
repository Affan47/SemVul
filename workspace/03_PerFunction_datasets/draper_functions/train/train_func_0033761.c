get_folder_tree_from_folderitem(FolderItem *item)
{
  PyObject *result;
  GList *walk;

  for(walk = folder_get_list(); walk; walk = walk->next) {
    Folder *folder = walk->data;
    if(folder->node) {
      GNode *root_node;

      root_node = g_node_find(folder->node, G_PRE_ORDER, G_TRAVERSE_ALL, item);
      if(!root_node)
        continue;

      result = NULL;
      if(!setup_folderitem_node(root_node, NULL, &result))
        return NULL;
      else
        return result;
    }
  }

  PyErr_SetString(PyExc_LookupError, "Folder not found");
  return NULL;
}
