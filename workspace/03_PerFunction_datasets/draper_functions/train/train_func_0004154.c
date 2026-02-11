init_route()
{
	int i;

	for(i=0;i<MAX_ROUTES;i++){
		rts[i].ipaddr = 0;
		rts[i].mask = 0xffffffff;
		rts[i].destif = NULL;
		rts[i].destaddr = 0;
		rts[i].destport = 0;
		rts[i].hits = 0;
	}
	rts_top = 0;

	rlineno = 0;
	rerrflag = 0;
}
