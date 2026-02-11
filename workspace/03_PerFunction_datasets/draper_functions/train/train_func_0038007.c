buildin_npcskillpos(struct script_state *st)
{
	struct block_list *bl = map_id2bl(st->oid);
	int skillid=conv_num(st,& (st->stack->stack_data[st->start+2]));
	int skilllv=conv_num(st,& (st->stack->stack_data[st->start+3]));
	int x=conv_num(st,& (st->stack->stack_data[st->start+4]));
	int y=conv_num(st,& (st->stack->stack_data[st->start+5]));

	if(bl == NULL || bl->type != BL_NPC) {
		struct map_session_data *sd = script_rid2sd(st);
		if(sd == NULL)
			return 0;
		bl = &sd->bl;
	}
	clif_skill_poseffect(bl,skillid,skilllv,x,y,gettick());

	return 0;
}
