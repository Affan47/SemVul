cloog_loop_generate(CloogLoop *loop, CloogDomain *context,
	int level, int scalar, int *scaldims, int nb_scattdims,
	CloogOptions *options)
{


  loop = cloog_loop_restrict_all(loop, context);
  if (!loop)
    return NULL;

  return cloog_loop_generate_restricted_or_stop(loop, context,
			      level, scalar, scaldims, nb_scattdims, options);
}
