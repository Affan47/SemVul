add_values( ValueMap & values_to_add) {
  ValueMap::const_iterator it;
  for ( it=values_to_add.begin() ; it != values_to_add.end(); it++ )
    values[it->first] = it->second;
}
