buildin_mes(struct script_state *st)
{
	char *str;

	str = conv_str(st,& (st->stack->stack_data[st->start+2]));
	if(*str)
		clif_scriptmes(script_rid2sd(st),st->oid,str);
	return 0;
}
