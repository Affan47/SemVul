kodak605_cmdline_arg(void *vctx, int argc, char **argv)
{
	struct kodak605_ctx *ctx = vctx;
	int i, j = 0;


	optind = 1;
	opterr = 0;
	while ((i = getopt(argc, argv, "C:ms")) >= 0) {
		switch(i) {
		case 'C':
			if (ctx) {
				j = kodak605_set_tonecurve(ctx, optarg);
				break;
			}
			return 1;
		case 'm':
			if (ctx) {
				j = kodak605_get_media(ctx);
				break;
			}
			return 1;
		case 's':
			if (ctx) {
				j = kodak605_get_status(ctx);
				break;
			}
			return 1;
		default:
			break;
		}

		if (j) return j;
	}

	return 0;
}
