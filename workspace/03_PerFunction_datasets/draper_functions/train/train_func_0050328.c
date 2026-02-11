process_u_diff(void *state_, char *line, unsigned long len)
{
	struct blame_diff_state *state = state_;
	struct chunk *chunk;
	int off1, off2, len1, len2, num;

	num = state->ret->num;
	if (len < 4 || line[0] != '@' || line[1] != '@') {
		if (state->hunk_in_pre_context && line[0] == ' ')
			state->ret->chunks[num - 1].same++;
		else {
			state->hunk_in_pre_context = 0;
			if (line[0] == ' ')
				state->hunk_post_context++;
			else
				state->hunk_post_context = 0;
		}
		return;
	}

	if (num && state->hunk_post_context) {
		chunk = &state->ret->chunks[num - 1];
		chunk->p_next -= state->hunk_post_context;
		chunk->t_next -= state->hunk_post_context;
	}
	state->ret->num = ++num;
	state->ret->chunks = xrealloc(state->ret->chunks,
				      sizeof(struct chunk) * num);
	chunk = &state->ret->chunks[num - 1];
	if (parse_hunk_header(line, len, &off1, &len1, &off2, &len2)) {
		state->ret->num--;
		return;
	}


	off1--;
	off2--;

	chunk->same = len2 ? off2 : (off2 + 1);

	chunk->p_next = off1 + (len1 ? len1 : 1);
	chunk->t_next = chunk->same + len2;
	state->hunk_in_pre_context = 1;
	state->hunk_post_context = 0;
}
