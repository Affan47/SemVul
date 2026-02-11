c_split_parallel_clauses (location_t loc, tree clauses,
			  tree *par_clauses, tree *ws_clauses)
{
  tree next;

  *par_clauses = NULL;
  *ws_clauses = build_omp_clause (loc, OMP_CLAUSE_NOWAIT);

  for (; clauses ; clauses = next)
    {
      next = OMP_CLAUSE_CHAIN (clauses);

      switch (OMP_CLAUSE_CODE (clauses))
	{
	case OMP_CLAUSE_PRIVATE:
	case OMP_CLAUSE_SHARED:
	case OMP_CLAUSE_FIRSTPRIVATE:
	case OMP_CLAUSE_LASTPRIVATE:
	case OMP_CLAUSE_REDUCTION:
	case OMP_CLAUSE_COPYIN:
	case OMP_CLAUSE_IF:
	case OMP_CLAUSE_NUM_THREADS:
	case OMP_CLAUSE_DEFAULT:
	  OMP_CLAUSE_CHAIN (clauses) = *par_clauses;
	  *par_clauses = clauses;
	  break;

	case OMP_CLAUSE_SCHEDULE:
	case OMP_CLAUSE_ORDERED:
	case OMP_CLAUSE_COLLAPSE:
	  OMP_CLAUSE_CHAIN (clauses) = *ws_clauses;
	  *ws_clauses = clauses;
	  break;

	default:
	  gcc_unreachable ();
	}
    }
}
