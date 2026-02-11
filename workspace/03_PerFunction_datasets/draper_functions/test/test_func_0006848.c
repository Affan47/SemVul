buildin_csvreadarray(struct script_state *st)
{
	int i;
	struct map_session_data *sd = NULL;
	char *file = conv_str(st,& (st->stack->stack_data[st->start+2]));
	int  row   = conv_num(st,& (st->stack->stack_data[st->start+3]));
	int  num;
	char *name;
	char prefix, postfix;
	struct csvdb_data* csv = script_csvload( file );

	if( st->stack->stack_data[st->start+4].type != C_NAME ) {
		printf("buildin_csvreadarray: param not name\n");
		return 0;
	}
	num     = st->stack->stack_data[st->start+4].u.num;
	name    = str_buf+str_data[num&0x00ffffff].str;
	prefix  = *name;
	postfix = name[strlen(name)-1];

	if( prefix != '$' && prefix != '@' && prefix != '\'' ) {
		printf("buildin_csvreadarray: illegal scope !\n");
		return 0;
	}
	if( prefix != '$' && prefix != '\'' ) {
		sd = script_rid2sd(st);
		if(sd == NULL)
			return 0;
	}


	for(i = getarraysize(st,num,postfix,st->stack->stack_data[st->start+4].ref) - (num >> 24) - 1;i >= 0;i--) {
		set_reg(st,sd,num+(i<<24),name,(postfix == '$')? "": 0,st->stack->stack_data[st->start+4].ref);
	}

	if( csv ) {
		const void *v;
		int max = csvdb_get_columns( csv, row );
		if( max + (num >> 24) > 128 ) {
			max = 128 - (num>>24);
		}
		for( i = 0; i < max; i++ ) {
			if( postfix == '$' )
				v = (const void *)csvdb_get_str(csv, row, i);
			else
				v = INT2PTR(csvdb_get_num(csv, row, i));
			set_reg(st,sd,num+(i<<24),name,v,st->stack->stack_data[st->start+4].ref);
		}
	}
	return 0;
}
