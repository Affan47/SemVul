buildin_checkequipedcard(struct script_state *st)
{
	struct map_session_data *sd=script_rid2sd(st);
	int c;

	c=conv_num(st,& (st->stack->stack_data[st->start+2]));

	if(sd){
		int n,i;
		for(i=0;i<MAX_INVENTORY;i++){
			if(sd->status.inventory[i].nameid > 0 && sd->status.inventory[i].amount){
				if(itemdb_isspecial(sd->status.inventory[i].card[0]))
					continue;
				for(n=0;n<4;n++){
					if(sd->status.inventory[i].card[n]==c){
						push_val(st->stack,C_INT,1);
						return 0;
					}
				}
			}
		}
	}
	push_val(st->stack,C_INT,0);
	return 0;
}
