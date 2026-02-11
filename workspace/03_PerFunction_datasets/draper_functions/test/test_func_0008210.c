deleteScope( const DefRecTypeT & type )
{
   vt_assert( type < DEF_REC_TYPE__Num );


   std::map<DefRecTypeT, TokenFactoryScopeI*>::iterator it = m_def2scope.find( type );


   if( it != m_def2scope.end() )
   {
      delete it->second;
      m_def2scope.erase( it );
   }
}
