atom_list() const
{
  Atom_list list;
  for ( int p = 0; p < children.size(); p++ )
    for ( int m = 0; m < children[p].size(); m++ )
      for ( int a = 0; a < children[p][m].size(); a++ )
        list.push_back( Atom( children[p][m][a] ) );
  return list;
}
