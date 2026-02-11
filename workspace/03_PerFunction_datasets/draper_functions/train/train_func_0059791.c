buildin_showdigit(struct script_state *st)
{
	struct map_session_data *sd = script_rid2sd(st);
	unsigned char type = 0;
	int value;

	nullpo_retr(0, sd);

	value = conv_num(st,& (st->stack->stack_data[st->start+2]));
	if( st->end > st->start+3 )
		type = conv_num(st,& (st->stack->stack_data[st->start+3]));

	if(type < 0 || type > 3)
		return 0;

	clif_showdigit(sd, type, value);
	return 0;
}
