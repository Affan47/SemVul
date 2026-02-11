usage(int is_long_help)
{
	fprintf(stderr, "\n");
	fprintf(stderr, "Usage:   samtools depad <in.bam>\n\n");
	fprintf(stderr, "Options: -s       output is SAM (default is BAM)\n");
	fprintf(stderr, "         -S       input is SAM (default is BAM)\n");
	fprintf(stderr, "         -u       uncompressed BAM output (can't use with -s)\n");
	fprintf(stderr, "         -1       fast compression BAM output (can't use with -s)\n");
	fprintf(stderr, "         -T FILE  padded reference sequence file [null]\n");
	fprintf(stderr, "         -o FILE  output file name [stdout]\n");
	fprintf(stderr, "         -?       longer help\n");
	fprintf(stderr, "\n");
	if (is_long_help)
		fprintf(stderr, "Notes:\n\
\n\
  1. Requires embedded reference sequences (before the reads for that reference),\n\
     or ideally a FASTA file of the padded reference sequences (via the -T argument).\n\
\n\
  2. The input padded alignment read's CIGAR strings must not use P or I operators.\n\
\n");
        return 1;
}
