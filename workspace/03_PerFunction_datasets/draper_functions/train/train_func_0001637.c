set_longest_orf(struct seq_col *in_seq_col)
{
	int i;

	struct seq_col *ret_seq_col;
	struct seq *seq, *input_seq;
	if((ret_seq_col = calloc(1,sizeof(struct seq_col)))==NULL)
	{
		error("set_longest_orf(): Out of memory ");
	}
	if((ret_seq_col->seqs = calloc((in_seq_col->length),sizeof(struct seq)))==NULL)
	{
		error("set_longest_orf(): Out of memory ");
	}

	input_seq = &(in_seq_col->seqs[0]);
	for(i=0; i!= in_seq_col->length; ++i)
	{
		seq = orf_finder(input_seq);
		++input_seq;
		ret_seq_col->seqs[i].dna_num = seq->dna_num;
		ret_seq_col->seqs[i].orf_frame = seq->orf_frame;
		ret_seq_col->seqs[i].data = seq->data;
		ret_seq_col->seqs[i].name = seq->name;
		ret_seq_col->seqs[i].num = seq->num;
		ret_seq_col->seqs[i].length = seq->length;
		++seq;

	}
	ret_seq_col->length=in_seq_col->length;

	return ret_seq_col;
}
