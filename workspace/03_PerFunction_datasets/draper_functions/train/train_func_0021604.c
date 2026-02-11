main_bamshuf(int argc, char *argv[])
{
	int c, n_files = 64, clevel = DEF_CLEVEL, is_stdout = 0, is_un = 0;
	while ((c = getopt(argc, argv, "n:l:uO")) >= 0) {
		switch (c) {
		case 'n': n_files = atoi(optarg); break;
		case 'l': clevel = atoi(optarg); break;
		case 'u': is_un = 1; break;
		case 'O': is_stdout = 1; break;
		}
	}
	if (is_un) clevel = 0;
	if (optind + 2 > argc) {
		fprintf(stderr, "\nUsage:   bamshuf [-Ou] [-n nFiles] [-c cLevel] <in.bam> <out.prefix>\n\n");
		fprintf(stderr, "Options: -O      output to stdout\n");
		fprintf(stderr, "         -u      uncompressed BAM output\n");
		fprintf(stderr, "         -l INT  compression level [%d]\n", DEF_CLEVEL);
		fprintf(stderr, "         -n INT  number of temporary files [%d]\n", n_files);
		fprintf(stderr, "\n");
		return 1;
	}
	bamshuf(argv[optind], n_files, argv[optind+1], clevel, is_stdout);
	return 0;
}
