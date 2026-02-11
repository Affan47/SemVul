operator[]( ArrayIndex index )
{
   JSON_ASSERT( type_ == nullValue  ||  type_ == arrayValue );
   if ( type_ == nullValue )
      *this = Value( arrayValue );
#ifndef JSON_VALUE_USE_INTERNAL_MAP
   CZString key( index );
   ObjectValues::iterator it = value_.map_->lower_bound( key );
   if ( it != value_.map_->end()  &&  (*it).first == key )
      return (*it).second;

   ObjectValues::value_type defaultValue( key, null );
   if ( it != value_.map_->end() )
   {
      it = value_.map_->insert( it, defaultValue );
   }
   else
   {
      std::pair<ObjectValues::iterator,bool> ret;
      ret = value_.map_->insert( defaultValue );
      it = ret.first;
   }
   return (*it).second;
#else
   return value_.array_->resolveReference( index );
#endif
}
