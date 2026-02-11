loc_exp_dep_alloc (variable var, int count)
{
  size_t allocsize;

  gcc_checking_assert (var->onepart);


  gcc_checking_assert (!count
		       || VAR_LOC_DEP_VEC (var) == NULL
		       || VAR_LOC_DEP_VEC (var)->is_empty ());

  if (VAR_LOC_1PAUX (var) && VAR_LOC_DEP_VEC (var)->space (count))
    return;

  allocsize = offsetof (struct onepart_aux, deps)
	      + vec<loc_exp_dep, va_heap, vl_embed>::embedded_size (count);

  if (VAR_LOC_1PAUX (var))
    {
      VAR_LOC_1PAUX (var) = XRESIZEVAR (struct onepart_aux,
					VAR_LOC_1PAUX (var), allocsize);


      if (VAR_LOC_DEP_LST (var))
	VAR_LOC_DEP_LST (var)->pprev = VAR_LOC_DEP_LSTP (var);
    }
  else
    {
      VAR_LOC_1PAUX (var) = XNEWVAR (struct onepart_aux, allocsize);
      *VAR_LOC_DEP_LSTP (var) = NULL;
      VAR_LOC_FROM (var) = NULL;
      VAR_LOC_DEPTH (var).complexity = 0;
      VAR_LOC_DEPTH (var).entryvals = 0;
    }
  VAR_LOC_DEP_VEC (var)->embedded_init (count);
}
