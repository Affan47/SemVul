isSymbolUsed(int symb_id) const
{
  for (variable_node_map_t::const_iterator it = variable_node_map.begin();
       it != variable_node_map.end(); it++)
    if (it->first.first == symb_id)
      return true;

  if (local_variables_table.find(symb_id) != local_variables_table.end())
    return true;

  return false;
}
