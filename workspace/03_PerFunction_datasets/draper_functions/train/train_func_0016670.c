docont()
{
    struct loopstruct *contloop;
    offset_T spmark;
    struct switchstruct *switchthen;

    for (contloop = loopnow, switchthen = switchnow; ;
	 contloop = contloop->prevloop, switchthen = switchthen->prevswitch)
    {
	if (contloop == NULL)
	{
	    badloop();
	    return;
	}
	if (contloop->contlab != 0)
	    break;
    }
    if (switchnow == NULL)
    {
	spmark = sp;
	modstk(contloop->spmark);
	sp = spmark;
    }
    else if (switchthen == NULL)
    {
	outaddsp();
	outshex(contloop->spmark);
	outminus();
	outswstacklab();
#ifdef MC6809
	outcregname(LOCAL);
#endif
#ifdef I80386
	if (i386_32)
	    bumplc2();
#endif
	outnl();
    }
    jump(contloop->contlab);
}
