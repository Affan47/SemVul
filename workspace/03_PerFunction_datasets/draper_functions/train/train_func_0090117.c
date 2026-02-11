make_eq_name( const std::string *name )
{
  std::pair<Function,bool> f = domain->functions().find_function( *name );
  if( f.second )
    {
      prepare_application( name );
      eq_expr = make_application();
    }
  else
    {

      eq_term = make_term( name );
      eq_expr = NULL;
    }
}
