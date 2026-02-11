per_cpu_symbol_search(char *symbol)
{
	struct syment *sp;
	char old[BUFSIZE];
	char *new;

	if (STRNEQ(symbol, "per_cpu__")) {
		if ((sp = symbol_search(symbol)))
			return sp;
		new = symbol + strlen("per_cpu__");
		if ((sp = symbol_search(new))) {
			if ((sp->type == 'V') || (is_percpu_symbol(sp)))
				return sp;
			if ((sp->type == 'd') &&
			    (st->__per_cpu_start == st->__per_cpu_end))
				return sp;
		}
	} else {
		if ((sp = symbol_search(symbol))) {
			if ((sp->type == 'V') || (is_percpu_symbol(sp)))
				return sp;
		}

		sprintf(old, "per_cpu__%s", symbol);
		if ((sp = symbol_search(old)))
			return sp;
	}

	if (CRASHDEBUG(1))
		error(INFO, "per_cpu_symbol_search(%s): NULL\n", symbol);

	return NULL;
}
