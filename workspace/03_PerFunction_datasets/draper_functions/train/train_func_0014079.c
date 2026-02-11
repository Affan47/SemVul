parse_udp(int *argc_p, char ***argv_p, struct tc_u32_sel *sel)
{
	int res = -1;
	int argc = *argc_p;
	char **argv = *argv_p;

	if (argc < 2)
		return -1;

	if (strcmp(*argv, "src") == 0) {
		NEXT_ARG();
		res = parse_u16(&argc, &argv, sel, 0, -1);
	} else if (strcmp(*argv, "dst") == 0) {
		NEXT_ARG();
		res = parse_u16(&argc, &argv, sel, 2, -1);
	} else
		return -1;

	*argc_p = argc;
	*argv_p = argv;
	return res;
}
