main_pe2cofq(int argc, char *argv[])
{
	gzFile fp1, fp2;
	kseq_t *seq[2];
	kstring_t str;

	if (argc < 3) {
		fprintf(stderr, "Usage: fermi pe2cofq <in1.fq> <in2.fq>\n");
		return 1;
	}
	str.l = str.m = 0; str.s = 0;
	fp1 = strcmp(argv[1], "-")? gzopen(argv[1], "r") : gzdopen(fileno(stdin), "r");
	fp2 = strcmp(argv[2], "-")? gzopen(argv[2], "r") : gzdopen(fileno(stdin), "r");
	seq[0] = kseq_init(fp1);
	seq[1] = kseq_init(fp2);
	while (kseq_read(seq[0]) >= 0) {
		if (kseq_read(seq[1]) < 0) break;
		str.l = 0;
		if (seq[0]->name.l > 2 && seq[0]->name.s[seq[0]->name.l-2] == '/' && isdigit(seq[0]->name.s[seq[0]->name.l-1]))
			seq[0]->name.s[(seq[0]->name.l -= 2)] = 0;
		seq[1]->name.l = 0;
		kputsn(seq[0]->name.s, seq[0]->name.l, &seq[1]->name);
		write_seq(seq[0], &str);
		write_seq(seq[1], &str);
		fputs(str.s, stdout);
	}
	kseq_destroy(seq[0]); gzclose(fp1);
	kseq_destroy(seq[1]); gzclose(fp2);
	free(str.s);
	return 0;
}
