concat(RegionList *l)
{
    SGREPDATA(l);
	ListIterator lp;
	RegionList *a;
	Region reg1,reg2;
#ifdef PROGRESS_REPORTS
	char *oper_name;
	int prog;int prog_start;
#endif

#ifdef DEBUG
	fprintf(stderr,"concat called\n");
#endif
	stats.concat++;
	a=new_region_list(sgrep);
	start_region_search(l,&lp);
	get_region(&lp,&reg1);


	if (reg1.start==-1) return a;

#ifdef PROGRESS_REPORTS
	oper_name="concat";
	prog=0;
	prog_start=LIST_SIZE(l);
#endif
	get_region(&lp,&reg2);

	while (reg2.start!=-1)
	{
		if (reg2.start>reg1.end+1)
		{

			add_region(a,reg1.start,reg1.end);
			reg1=reg2;
		} else if ( reg2.end>reg1.end )
		{

			reg1.end=reg2.end;
		}
		get_region(&lp,&reg2);
	}
	add_region(a,reg1.start,reg1.end);
	return a;
}
