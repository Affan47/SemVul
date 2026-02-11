getreg(char *oper)
{
	register struct result *r;
	register int i;
	char *oper2;

	for (i=0; i<6; i++)
		if (filter (oper,indexed[i],&oper2))
		{	offset = 0;
			if ( i>1)
			{	r=parse(oper2);
				checktype(r,L_ABSOLUTE);
				offset = r->value;
				if (i>3)
					offset = -offset;
			};

			if (indexflag || offsetflag )
				error(badop);
			offsetflag=TRUE;
			indexflag = i&1 ? IY : IX;
			return MREGISTER;
		};
	if (filter(oper,"(_HL_)"))
	{	if (indexflag && indexflag != HL)
			error(badop);
		indexflag=HL;
		return MREGISTER;
	}
	if (filter(oper,"(_BC_)"))
		return SPBC;
	if (filter(oper,"(_DE_)"))
		return SPDE;
	if (filter(oper,"(_?_)",&oper2))
	{	r=parse(oper2);
		checktype(r,L_ABSOLUTE);
		if (arg8flag || arg16flag)
			error(badop);
		arg16flag=TRUE;
		arg=r->value;
		return MEMORY;
	}
	r=parse(oper);
	if (r->type == L_ABSOLUTE)
	{	if (arg8flag || arg16flag)
			error(badop);
		arg16flag=TRUE;
		arg=r->value;
		return IMDATA;
	};
	checktype(r,L_REGS);
	if ( r->value != (1 << r->modifier) )
		error ("illegal register list");

	if (r->modifier==12 || r->modifier==13 || r->modifier==HLREGISTER )
	{	switch (r->modifier)
		{
		case 12: i=IX;	break;
		case 13: i=IY;	break;
		default: i=HL;	break;
		}
		if (indexflag && indexflag != i)
			error(badop);
		indexflag=i;
		return HLREGISTER;
	}
	return r->modifier;
}
