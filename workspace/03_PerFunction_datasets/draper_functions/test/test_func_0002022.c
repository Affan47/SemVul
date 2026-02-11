egg_tree_multi_drag_source_drag_data_get (EggTreeMultiDragSource *drag_source,
					  GdkDragContext         *context,
					  GtkSelectionData       *selection_data,
					  GList                  *path_list)
{
  EggTreeMultiDragSourceInterface *iface = EGG_TREE_MULTI_DRAG_SOURCE_GET_IFACE (drag_source);

  g_return_val_if_fail (EGG_IS_TREE_MULTI_DRAG_SOURCE (drag_source), FALSE);
  g_return_val_if_fail (iface->drag_data_get != NULL, FALSE);
  g_return_val_if_fail (path_list != NULL, FALSE);
  g_return_val_if_fail (selection_data != NULL, FALSE);

  return (* iface->drag_data_get) (drag_source, context, selection_data, path_list);
}
