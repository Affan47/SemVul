set_types( const std::string & arg,
                std::string & types1, std::string & types2 )
  {
  std::string * p = &types1;
  bool error = false, comma_found = false;
  types1.clear();
  types2.clear();

  for( unsigned i = 0; i < arg.size(); ++i )
    {
    const char ch = arg[i];
    if( ch == ',' )
      {
      if( comma_found ) { error = true; break; }
      else { comma_found = true; p = &types2; continue; }
      }
    if( !Sblock::isstatus( ch ) ) { error = true; break; }
    *p += ch;
    }
  if( types1.size() == 0 || types2.size() == 0 ) error = true;
  if( error )
    {
    show_error( "Invalid type for 'change-types' option.", 0, true );
    std::exit( 1 );
    }
  if( types1.size() > types2.size() )
    types2.append( types1.size() - types2.size(), types2[types2.size()-1] );
  }
