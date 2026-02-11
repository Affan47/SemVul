buildin_pcblockmove(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	int flag;

	nullpo_retr(0, sd);

	flag = conv_num(st,& (st->stack->stack_data[st->start+2]));

	unit_stop_walking(&sd->bl,1);
	sd->state.blockedmove = flag > 0;

	return 0;
}
