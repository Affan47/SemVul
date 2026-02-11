print( std::ostream &os ) const
{
  os << "[";
  for( size_t i = 0; i < size(); ++i )
    {
      atom_list( i ).print( os );
      if( i + 1 < size() ) os << ",";
    }
  os << "]";
}
