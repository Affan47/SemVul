getarraysize(struct script_state *st,int num,char postfix,struct linkdb_node** ref)
{
	int i = num>>24;
	int c = (i == 0)? -1: i;

	for(; i<128; i++) {
		void *v = get_val2(st,(num & 0x00FFFFFF)+(i<<24),ref);
		if( postfix == '$' && *((char*)v) )
			c = i;
		if( postfix != '$' && PTR2INT(v) )
			c = i;
	}
	return c+1;
}
