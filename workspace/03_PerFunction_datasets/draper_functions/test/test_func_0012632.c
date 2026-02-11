buildin_getonlineguildmember(struct script_state *st)
{
	struct guild *g = NULL;

	if(st->end>st->start+2) {
		g = guild_search(conv_num(st,&(st->stack->stack_data[st->start+2])));
	} else {
		struct map_session_data *sd = script_rid2sd(st);
		if(sd)
			g = guild_search(sd->status.guild_id);
	}
	push_val(st->stack,C_INT,((g != NULL)? g->connect_member: 0));

	return 0;
}
