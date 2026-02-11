set_key_value(const TreeModel::iterator& iter, const DbValue& value)
{

  if(check_treeiter_validity(iter))
  {
    type_datamodel_row_index datamodel_row = get_datamodel_row_index_from_tree_row_iter(iter);
    m_map_rows[datamodel_row].m_key = value;
  }
}
