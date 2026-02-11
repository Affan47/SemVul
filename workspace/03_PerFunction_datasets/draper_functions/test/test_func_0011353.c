p_ere(p, stop)
register struct parse *p;
int stop;
{
	register char c;
	register sopno UNINIT_VAR(prevback);
	register sopno UNINIT_VAR(prevfwd);
	register sopno conc;
	register int first = 1;

	for (;;) {

		conc = HERE();
		while (MORE() && (c = PEEK()) != '|' && c != stop)
		{
		  if (my_regex_enough_mem_in_stack &&
		      my_regex_enough_mem_in_stack(0))
		  {
		    SETERROR(REG_ESPACE);
		    return;
		  }
		  p_ere_exp(p);
		}
		if(REQUIRE(HERE() != conc, REG_EMPTY)) {}

		if (!EAT('|'))
			break;

		if (first) {
			INSERT(OCH_, conc);
			prevfwd = conc;
			prevback = conc;
			first = 0;
		}
		ASTERN(OOR1, prevback);
		prevback = THERE();
		AHEAD(prevfwd);
		prevfwd = HERE();
		EMIT(OOR2, 0);
	}

	if (!first) {
		AHEAD(prevfwd);
		ASTERN(O_CH, prevback);
	}

	assert(!MORE() || SEE(stop));
}
