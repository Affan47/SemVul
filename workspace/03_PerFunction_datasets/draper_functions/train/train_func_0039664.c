tweak_poolparam(struct cli *cli, const struct parspec *par, const char *arg)
{
	volatile struct poolparam *pp, px;
	char **av;

	pp = par->priv;
	if (arg == NULL) {
		VCLI_Out(cli, "%u,%u,%g",
		    pp->min_pool, pp->max_pool, pp->max_age);
	} else {
		av = VAV_Parse(arg, NULL, ARGV_COMMA);
		do {
			if (av[0] != NULL) {
				VCLI_Out(cli, "Parse error: %s", av[0]);
				VCLI_SetResult(cli, CLIS_PARAM);
				break;
			}
			if (av[1] == NULL || av[2] == NULL || av[3] == NULL) {
				VCLI_Out(cli,
				    "Three fields required:"
				    " min_pool, max_pool and max_age\n");
				VCLI_SetResult(cli, CLIS_PARAM);
				break;
			}
			px = *pp;
			if (tweak_generic_uint(cli, &px.min_pool, av[1],
			    (uint)par->min, (uint)par->max))
				break;
			if (tweak_generic_uint(cli, &px.max_pool, av[2],
			    (uint)par->min, (uint)par->max))
				break;
			if (tweak_generic_timeout_double(cli, &px.max_age,
			    av[3], 0, 1e6))
				break;
			if (px.min_pool > px.max_pool) {
				VCLI_Out(cli,
				    "min_pool cannot be larger"
				    " than max_pool\n");
				VCLI_SetResult(cli, CLIS_PARAM);
				break;
			}
			*pp = px;
		} while(0);
	}
}
