get ( int id )
{
   IdentCache::iterator f = identCache.find ( id );
   if ( f != identCache.end() )
      return &(*(f->second));
   else
      return NULL;
}
