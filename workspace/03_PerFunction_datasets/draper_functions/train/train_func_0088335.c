collect_ctx(ctx_stat *s)
{
	ullong data[1];
	ullong old;

	if (rdval(get_file(&proc_stat), "ctxt", data, 1)) {
		put_question_marks(4);
		return;
	}

	old = s->old;
	if (data[0] < old) old = data[0];
	s->old = data[0];
	scale(data[0] - old);
}
