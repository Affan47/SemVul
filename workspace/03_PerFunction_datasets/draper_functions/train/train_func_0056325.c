rd_network( simfile, prefix, has_param_file )
  char  *simfile;
  char  *prefix;
  int   has_param_file;
  {
    static int      firstcall = 1;

    if( firstcall )
      {
	rd_tlist = NULL;
	init_counts();
	init_listTbl();

	VDD_node = RsimGetNode( "Vdd" );
	VDD_node->npot = HIGH;
	VDD_node->nflags |= (INPUT | POWER_RAIL);
	VDD_node->head.inp = 1;
	VDD_node->head.val = HIGH;
	VDD_node->head.punt = 0;
	VDD_node->head.time = 0;
	VDD_node->head.t.r.rtime = VDD_node->head.t.r.delay = 0;
	VDD_node->head.next = last_hist;
	VDD_node->curr = &(VDD_node->head);

	GND_node = RsimGetNode( "Gnd" );
	GND_node->npot = LOW;
	GND_node->nflags |= (INPUT | POWER_RAIL);
	GND_node->head.inp = 1;
	GND_node->head.val = LOW;
	GND_node->head.punt = 0;
	GND_node->head.time = 0;
	GND_node->head.t.r.rtime = GND_node->head.t.r.delay = 0;
	GND_node->head.next = last_hist;
	GND_node->curr = &(GND_node->head);

	NEW_TRANS( tcap );
	tcap->scache.t = tcap->dcache.t = tcap;
	tcap->x.pos = 0;

	firstcall = 0;
      }
    nerrs = 0;

    simprefix = prefix;
    isBinFile = input_sim( simfile, has_param_file );
    simprefix = (char *)NULL;

    if (nerrs > 0)
#ifndef TCL_IRSIM
	exit( 1 );
#else
    {
	lprintf(stderr, "Errors occurred on reading input file %s\n", simfile);
	return 1;
    }
    else
	return 0;
#endif
  }
