buildin_gettimestr(struct script_state *st)
{
	char *tmpstr, *fmtstr;
	int maxlen;
	time_t now = time(NULL);

	fmtstr = conv_str(st,& (st->stack->stack_data[st->start+2]));
	maxlen = conv_num(st,& (st->stack->stack_data[st->start+3]));

	tmpstr = (char *)aCalloc(maxlen+1,sizeof(char));
	if( !strftime(tmpstr,maxlen+1,fmtstr,localtime(&now)) ) {
		printf("buildin_gettimestr: maxlen is too short!!\n");
	}
	tmpstr[maxlen] = '\0';

	push_str(st->stack,C_STR,tmpstr);
	return 0;
}
