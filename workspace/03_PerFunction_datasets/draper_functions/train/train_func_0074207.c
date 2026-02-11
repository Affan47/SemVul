match( const StateFormula &formula, VarSubstMap &subst ) const
{
  const Exists *ex = dynamic_cast<const Exists*>( &formula );
  if( (ex != NULL) && (parameters_.size() == ex->parameters_.size()) )
    {

      VarSubstMap nsubst = subst;
      for( size_t i = 0; i < arity(); ++i )
	nsubst[parameter(i)] = ex->parameter(i);


      return( body().match( ex->body(), nsubst ) );
    }
  return( false );
}
