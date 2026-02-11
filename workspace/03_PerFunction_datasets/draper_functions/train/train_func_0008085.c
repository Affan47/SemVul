buildin_getequippercentrefinery(struct script_state *st)
{
	int num, i = -1;
	struct map_session_data *sd;

	num=conv_num(st,& (st->stack->stack_data[st->start+2]));
	sd=script_rid2sd(st);
	if(num > 0 && num <= EQUIP_INDEX_MAX)
		i=pc_checkequip(sd,equip_pos[num-1]);
	if(i >= 0)
		push_val(st->stack,C_INT,status_percentrefinery(sd,&sd->status.inventory[i]));
	else
		push_val(st->stack,C_INT,0);

	return 0;
}
