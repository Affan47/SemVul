make_exists( const StateFormula& body )
{
  context.pop_frame();
  size_t n, m = quantified.size() - 1;
  for( n = m; is_variable( quantified[n] ); --n );
  if( n < m )
    {
      Exists* exists = new Exists;
      for( size_t i = n + 1; i <= m; ++i )
	exists->add_parameter( quantified[i] );
      exists->set_body( body );
      StateFormula::unregister_use( &body );
      quantified.resize( n );
      return( exists );
    }
  else
    {
      quantified.pop_back();
      return( &body );
    }
}
