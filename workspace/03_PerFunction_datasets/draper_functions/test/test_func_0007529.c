_print_aliases (char* node_hostname)
{
	char me[MAX_SLURM_NAME], *n = NULL, *a = NULL;
	char *s;

	slurm_conf_init(NULL);
	if (!node_hostname) {
		gethostname_short(me, MAX_SLURM_NAME);
		s = me;
	} else
		s = node_hostname;

	if (!(n = slurm_conf_get_aliases(s)) && (s == me)) {

		if (!(a = slurm_conf_get_aliased_nodename()))
			a = slurm_conf_get_nodename("localhost");

		if (a) {
			n = slurm_conf_get_aliases(a);
			xfree(a);
		}
	}

	if (n) {
		fprintf(stdout, "%s\n", n);
		xfree(n);
	}

}
