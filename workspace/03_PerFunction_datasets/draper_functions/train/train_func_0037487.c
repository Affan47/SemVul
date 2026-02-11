buildin_getareadropitem(struct script_state *st)
{
	char *str;
	int m,x0,y0,x1,y1,item=0,amount=0;
	struct script_data *data;

	str = conv_str(st,& (st->stack->stack_data[st->start+2]));
	x0  = conv_num(st,& (st->stack->stack_data[st->start+3]));
	y0  = conv_num(st,& (st->stack->stack_data[st->start+4]));
	x1  = conv_num(st,& (st->stack->stack_data[st->start+5]));
	y1  = conv_num(st,& (st->stack->stack_data[st->start+6]));

	data = &(st->stack->stack_data[st->start+7]);
	get_val(st,data);
	if( isstr(data) ) {
		const char *name = conv_str(st,data);
		struct item_data *item_data = itemdb_searchname(name);
		if(item_data)
			item = item_data->nameid;
	} else {
		item = conv_num(st,data);
	}

	m = script_mapname2mapid(st,str);
	if(m < 0) {
		push_val(st->stack,C_INT,-1);
		return 0;
	}
	if(item > 0) {
		amount = map_foreachinarea(buildin_getareadropitem_sub,m,x0,y0,x1,y1,BL_ITEM,item);
	}
	push_val(st->stack,C_INT,amount);

	return 0;
}
