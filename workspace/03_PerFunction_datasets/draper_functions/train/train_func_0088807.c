consume_line(void *state_, char *line, unsigned long len)
{
	struct combine_diff_state *state = state_;
	if (5 < len && !memcmp("@@ -", line, 4)) {
		if (parse_hunk_header(line, len,
				      &state->ob, &state->on,
				      &state->nb, &state->nn))
			return;
		state->lno = state->nb;
		if (!state->nb)


			state->nb = 1;
		if (state->nn == 0)


			state->lost_bucket = &state->sline[state->nb];
		else
			state->lost_bucket = &state->sline[state->nb-1];
		if (!state->sline[state->nb-1].p_lno)
			state->sline[state->nb-1].p_lno =
				xcalloc(state->num_parent,
					sizeof(unsigned long));
		state->sline[state->nb-1].p_lno[state->n] = state->ob;
		return;
	}
	if (!state->lost_bucket)
		return;
	switch (line[0]) {
	case '-':
		append_lost(state->lost_bucket, state->n, line+1, len-1);
		break;
	case '+':
		state->sline[state->lno-1].flag |= state->nmask;
		state->lno++;
		break;
	}
}
