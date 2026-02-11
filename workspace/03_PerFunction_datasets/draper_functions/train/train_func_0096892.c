bam_merge(int argc, char *argv[])
{
	int c, is_by_qname = 0, flag = 0, ret = 0;
	char *fn_headers = NULL, *reg = 0;

	while ((c = getopt(argc, argv, "h:nruR:")) >= 0) {
		switch (c) {
		case 'r': flag |= MERGE_RG; break;
		case 'h': fn_headers = strdup(optarg); break;
		case 'n': is_by_qname = 1; break;
		case 'u': flag |= MERGE_UNCOMP; break;
		case 'R': reg = strdup(optarg); break;
		}
	}
	if (optind + 2 >= argc) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Usage:   samtools merge [-nr] [-h inh.sam] <out.bam> <in1.bam> <in2.bam> [...]\n\n");
		fprintf(stderr, "Options: -n       sort by read names\n");
		fprintf(stderr, "         -r       attach RG tag (inferred from file names)\n");
		fprintf(stderr, "         -u       uncompressed BAM output\n");
		fprintf(stderr, "         -R STR   merge file in the specified region STR [all]\n");
		fprintf(stderr, "         -h FILE  copy the header in FILE to <out.bam> [in1.bam]\n\n");
		fprintf(stderr, "Note: Samtools' merge does not reconstruct the @RG dictionary in the header. Users\n");
		fprintf(stderr, "      must provide the correct header with -h, or uses Picard which properly maintains\n");
		fprintf(stderr, "      the header dictionary in merging.\n\n");
		return 1;
	}
	if (bam_merge_core(is_by_qname, argv[optind], fn_headers, argc - optind - 1, argv + optind + 1, flag, reg) < 0) ret = 1;
	free(reg);
	free(fn_headers);
	return ret;
}
