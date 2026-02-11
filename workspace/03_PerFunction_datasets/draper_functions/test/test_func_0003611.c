get_is_placeholder(const TreeModel::iterator& iter) const
{

  if(check_treeiter_validity(iter))
  {
    type_datamodel_row_index datamodel_row = get_datamodel_row_index_from_tree_row_iter(iter);
    return (datamodel_row == ((type_datamodel_row_index)get_internal_rows_count() -1));
  }

  return false;
}
