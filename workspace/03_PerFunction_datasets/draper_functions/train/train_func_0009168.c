seq_write(mame_file *f, const InputSeq *seq)
{
	int j, len;

	for (len = 0; len < SEQ_MAX; ++len)
		if ((*seq)[len] == CODE_NONE)
			break;

	writeword(f, len);
	for (j = 0; j < len; ++j)
		writeint(f, code_to_savecode((*seq)[j]));
}
