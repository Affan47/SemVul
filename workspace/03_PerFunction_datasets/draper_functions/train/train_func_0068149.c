make_term( const std::string *name )
{
  if( (*name)[0] == '?' )
    {
      std::pair<Variable,bool> v = context.find( *name );
      if( !v.second )
	{
	  if( problem != NULL )
	    v.first = problem->terms().add_variable( OBJECT_TYPE );
	  else
	    v.first = domain->terms().add_variable( OBJECT_TYPE );
	  context.insert( *name, v.first );
	  yyerror( "free variable `" + *name + "' used" );
	}
      delete name;
      return( v.first );
    }
  else
    {
      TermTable& terms = (problem!=NULL?problem->terms():domain->terms());
      const PredicateTable& predicates = domain->predicates();
      std::pair<Object,bool> o = terms.find_object( *name );
      if( !o.second )
	{
	  size_t n = term_parameters.size();
	  if( parsing_atom && (predicates.arity( atom_predicate ) > n) )
	    o.first = terms.add_object( *name, predicates.parameter( atom_predicate, n ) );
	  else
	    o.first = terms.add_object( *name, OBJECT_TYPE );
	}
      delete name;
      return( o.first );
    }
}
