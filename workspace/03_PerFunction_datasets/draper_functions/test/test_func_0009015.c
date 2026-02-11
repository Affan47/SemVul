instantiation( const SubstitutionMap& subst,
			   const problem_t& problem ) const
{
  return( *new Assignment( operator_,
			   application_->substitution( subst ),
			   expr_->instantiation( subst, problem ) ) );
}
