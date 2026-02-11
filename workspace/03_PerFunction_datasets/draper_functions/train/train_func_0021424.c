arrayexpr_next_fn(PredIterInfo info)
{
	ArrayExprIterState *state = (ArrayExprIterState *) info->state;

	if (state->next == NULL)
		return NULL;
	lsecond(state->opexpr.args) = lfirst(state->next);
	state->next = lnext(state->next);
	return (Node *) &(state->opexpr);
}
