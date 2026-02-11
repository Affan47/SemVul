components( TypeSet& components, Type type ) const
{
  if( type < 0 )
    components.insert( utypes_[-type - 1]->begin(), utypes_[-type - 1]->end() );
  else if( type != OBJECT_TYPE )
    components.insert( type );
}
