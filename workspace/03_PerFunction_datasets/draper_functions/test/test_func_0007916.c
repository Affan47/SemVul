cloog_loop_from_domain(CloogState *state, CloogDomain *domain,
	int number)
{
  int nb_iterators;
  CloogLoop * loop ;
  CloogStatement * statement ;


  loop = cloog_loop_malloc(state);

  loop->domain = domain;
  if (loop->domain != NULL)
    nb_iterators = cloog_domain_dimension(loop->domain);
  else
  nb_iterators = 0 ;

  statement = cloog_statement_alloc(state, number + 1);
  loop->block = cloog_block_alloc(statement, 0, NULL, nb_iterators);

  return loop ;
}
