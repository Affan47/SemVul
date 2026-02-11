getsize (siz)

unsigned long siz [];

  {
  long i;

  for (i=0 ; i<MAXCMD_DFN ; i++)
    siz [i] = 0;


  siz [character_DFN] = sizeof (char);
  siz [short_DFN]     = sizeof (short);
  siz [integer_DFN]   = sizeof (int);
  siz [long_DFN]      = sizeof (long);
  siz [string_DFN]    = sizeof (char *);

  siz [chain_DFN]     = sizeof (struct chain);
  siz [ptype_DFN]     = sizeof (struct ptype);

  siz [befig_DFN]     = sizeof (struct befig);
  siz [bereg_DFN]     = sizeof (struct bereg);
  siz [bemsg_DFN]     = sizeof (struct bemsg);
  siz [berin_DFN]     = sizeof (struct berin);
  siz [beout_DFN]     = sizeof (struct beout);
  siz [bebus_DFN]     = sizeof (struct bebus);
  siz [beaux_DFN]     = sizeof (struct beaux);
  siz [bedly_DFN]     = sizeof (struct beaux);
  siz [bebux_DFN]     = sizeof (struct bebux);
  siz [bepor_DFN]     = sizeof (struct bepor);
  siz [begen_DFN]     = sizeof (struct begen);
  siz [biabl_DFN]     = sizeof (struct biabl);
  siz [binode_DFN]    = sizeof (struct binode);
  siz [bequad_DFN]    = sizeof (struct bequad);
  siz [beder_DFN]     = sizeof (struct beder);
  }
