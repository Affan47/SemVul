dumpone(register u_int32_t a, register u_char *e, register time_t t,
    register char *h, char *interface)
{
	(void)fprintf(dumpf, "%s\t%s\t%u\t%s\t%s\n", e2str(e), intoa(a),
		      (u_int32_t)t, ((h != NULL)?h:""),
		      ((interface != NULL)?interface:""));
}
