shallow_find( const std::string &name ) const
  {
    VariableMap::const_iterator vi = frames_.back().find( name );
    if( vi != frames_.back().end() )
      return( std::make_pair( (*vi).second, true ) );
    else
      return( std::make_pair( 0, false ) );
  }
