asc_environment(int exportme, char *varlist, char ***env)
{
	extern char	**environ;
	char		**p;
	char		*v;
	int		nenv;
        char bad_string[] = "LAM_MPI_SESSION_PREFIX=";

	nenv = sfh_argv_count(*env);

	if (exportme)


		for (p = environ; p && *p; p++) {
		  if (strncmp(*p, "LAM_MPI_", 8) == 0 &&
                      strncmp(*p, bad_string, sizeof(bad_string) - 1) != 0) {
		    if (sfh_argv_add(&nenv, env, *p))
		      return LAMERROR;
		  }
#if LAM_WANT_IMPI
		  else if (strncmp(*p, "LAM_IMPI_", 8) == 0) {
		    if (sfh_argv_add(&nenv, env, *p))
		      return LAMERROR;
		  }
		  else if (strncmp(*p, "IMPI_", 5) == 0) {
		    if (sfh_argv_add(&nenv, env, *p))
		      return LAMERROR;
		  }
#endif


		  else if (strncmp(*p, "PBS_ENVIRONMENT=", 16) == 0) {
		    if (sfh_argv_add(&nenv, env, *p))
		      return LAMERROR;
		  }
		  else if (strncmp(*p, "PBS_JOBID=", 10) == 0) {
		    if (sfh_argv_add(&nenv, env, *p))
		      return LAMERROR;
		  }
		}


	if (varlist) {
		v = varlist + strlen(varlist);

		while (v != varlist) {

			for ( ; *v != ',' && v != varlist; v--) ;

			if (v != varlist) {
				if (*(v-1) != '\\') {

					if (add_var(&nenv, env, v+1))
						return(LAMERROR);
					*v = 0;
				}

				v--;
			}
		}


		if (add_var(&nenv, env, varlist))
			return(LAMERROR);
	}

	return 0;
}
