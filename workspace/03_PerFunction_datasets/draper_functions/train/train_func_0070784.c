buildin_delcartitem(struct script_state *st)
{
	int nameid=0,amount,i;
	int skip_egg = 0;
	struct map_session_data *sd = script_rid2sd(st);
	struct script_data *data;

	nullpo_retr(0, sd);

	data = &(st->stack->stack_data[st->start+2]);
	get_val(st,data);
	if( isstr(data) ) {
		const char *name = conv_str(st,data);
		struct item_data *item_data = itemdb_searchname(name);
		if(item_data)
			nameid = item_data->nameid;
	} else {
		nameid = conv_num(st,data);
	}
	if(nameid <= 0)
		return 0;

	amount = conv_num(st,& (st->stack->stack_data[st->start+3]));
	if(st->end > st->start+4)
		skip_egg = conv_num(st,& (st->stack->stack_data[st->start+4]));

	for(i=0; i<MAX_CART; i++) {
		if(sd->status.cart[i].nameid == nameid) {
			if(!skip_egg &&
			   itemdb_search(nameid)->flag.pet_egg &&
			   sd->status.cart[i].amount > 0 &&
			   sd->status.cart[i].card[0] == (short)0xff00 &&
			   pet_search_data(nameid, PET_EGG) != NULL)
			{
				intif_delete_petdata(*((int *)(&sd->status.cart[i].card[1])));
			}

			if(sd->status.cart[i].amount >= amount) {
				pc_cart_delitem(sd,i,amount,!pc_iscarton(sd));
				break;
			} else {
				amount -= sd->status.cart[i].amount;
				pc_cart_delitem(sd,i,sd->status.cart[i].amount,!pc_iscarton(sd));
			}
		}
	}

	return 0;
}
