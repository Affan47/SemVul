operator()( const Application* a1, const Application* a2 ) const
{
  if( a1->function() < a2->function() )
    return( true );
  else if( a1->function() > a2->function() )
    return( false );
  else
    {
      for( size_t i = 0; i < a1->arity(); ++i )
	{
	  if( a1->term(i) < a2->term( i ) )
	    return( true );
	  else if( a1->term(i) > a2->term( i ) )
	    return( false );
	}
      return( false );
    }
}
