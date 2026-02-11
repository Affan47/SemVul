Xcpu(int modifier, char *label, char *mnemo, char *oper)
{
	struct cpulist *q;
	char *a;
	extern struct cpulist cpulist[];

	if ( !oper )
		error ( "Need CPU name" );
	if ( asmflags & F_CPU_GV )
		error ( "One CPU only!" );

	q=cpulist;
	while ( q->name )
	{	if ( filter(oper,q->name,&a,&a,&a,&a) )
			break;
		else
			q++;
	}

	if ( ! q->name )
		error ( "Unknown CPU name" );

	if ( passnumber==2 )
		asmflags |= F_CPU_GV;
	(*q->init)(q->code);
        return 0;
}
