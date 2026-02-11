load_seqs_two_files(FILE * f1, int * end1, FILE * f2, int * end2)
{
	num_seqs = 0;
	int count1 = sequence_count(f1);
	int count2 = sequence_count(f2);

	all_seqs = malloc((count1+count2)*sizeof(struct cseq *));
	struct cseq *c;

	while((c = cseq_read(f1))) {
		all_seqs[num_seqs++] = c;
	}

	*end1 = num_seqs;

	while((c = cseq_read(f2))) {
		all_seqs[num_seqs++] = c;
	}

	*end2 = num_seqs;

	return num_seqs;

}
