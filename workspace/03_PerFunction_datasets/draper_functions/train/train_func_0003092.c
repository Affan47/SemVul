mutexchk(struct ao_opt *opt)
{
	struct ao_opt	*p;

	for (p = opt->aoo_mutex; p && (p != opt); p = p->aoo_mutex) {
		if (p->aoo_flags & AOTAKEN) return(LAMERROR);
	}

	return(0);
}
