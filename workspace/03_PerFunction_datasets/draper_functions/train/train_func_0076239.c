rewrite( std::map<const StateFormula*,
			                              const Atom*> &hash ) const
{
  ProbabilisticEffect *prob = new ProbabilisticEffect;
  for( size_t i = 0; i < size(); ++i )
    prob->add_outcome( probability( i ), effect( i ).rewrite( hash ) );
  return( *prob );
}
