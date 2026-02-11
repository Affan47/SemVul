tcpoptstrip_tg_help(void)
{
	const struct tcp_optionmap *w;

	printf(
"TCPOPTSTRIP target options:\n"
"  --strip-options value     strip specified TCP options denoted by value\n"
"                            (separated by comma) from TCP header\n"
"  Instead of the numeric value, you can also use the following names:\n"
	);

	for (w = tcp_optionmap; w->name != NULL; ++w)
		printf("    %-14s    strip \"%s\" option\n", w->name, w->desc);
}
