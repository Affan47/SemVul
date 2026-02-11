collect_blk(blk_stat *s)
{
	ullong data[2];
	int i;

	if (is26) {
		i = rdval_diskstats(get_file(&proc_diskstats), data);
	} else {
		i = rdval(get_file(&proc_stat), s->lookfor, data, 1, 2);

		data[0] *= 2;
		data[1] *= 2;
	}
	if (i) {
		put_question_marks(9);
		return;
	}

	for (i=0; i<2; i++) {
		ullong old = s->old[i];
		if (data[i] < old) old = data[i];
		s->old[i] = data[i];
		data[i] -= old;
	}
	scale(data[0]*512);
	put_c(' ');
	scale(data[1]*512);
}
