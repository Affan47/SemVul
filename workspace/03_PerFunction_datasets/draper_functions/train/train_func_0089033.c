asc_free(LIST *appd)
{
	struct aschema	*pp;
	struct apparg	*pa;
	struct appenv	*pe;

	if (appd == 0) return;

	for (pp = (struct aschema *) al_top(appd); pp;
			pp = (struct aschema *) al_next(appd, pp)) {

		if (pp->asc_nodelist) {
			al_free(pp->asc_nodelist);
		}

		pa = pp->asc_args;
		if (--pa->apa_refcount == 0) {
			sfh_argv_free(pa->apa_argv);
			free((char *) pa);
		}

		pe = pp->asc_env;
		if (--pe->ape_refcount == 0) {
		  sfh_argv_free(pe->ape_envv);
		  if (pe->ape_wrkdir) {
		    free(pe->ape_wrkdir);
		  }
		  free((char *) pe);
		}
	}

	al_free(appd);
}
