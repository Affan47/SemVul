Response_addnewtype(char *name, char *levels, char *matches, char type)


{
	int	match_all = 0;
	u_long 	l = 0L;
	rtype	*rt;

	if(!rmquotes(name))
		return -1;

	if(isequal(matches,"*"))
		match_all = 1;
	else if(!rmquotes(matches))
		return -2;


	User_str2flags(levels,&l);


	rt = rtype_new();
	Response_appendtype(rt);


	rtype_setname(rt,name);
	if(match_all)
		Response_addrtypematches(rt,"*");
	else
		Response_addrtypematches(rt,matches);
	rt->type = type;
	rt->level = l;

	return 0;
}
