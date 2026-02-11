buildin_getquestmaxcount(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	struct quest_data *qd;
	int quest_id, idx = 0, ret = 0;

	quest_id = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if(st->end>st->start+3)
		idx = conv_num(st,& (st->stack->stack_data[st->start+3]));

	qd = quest_get_data(sd, quest_id);
	if(qd) {
		if(idx < 0 || idx >= 3)
			idx = 0;
		ret = qd->mob[idx].max;
	}
	push_val(st->stack,C_INT, ret);

	return 0;
}
