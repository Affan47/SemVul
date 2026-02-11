setdbg()
  {
    static char  *dbg[] = { "ev", "dc", "tau", "taup", "spk", "tw", NULL };
    int          new;

    new = do_flags( debug, "Debug", "off", dbg );
    if( new != debug )
      {
	debug = new;
	targc = 1;
	(void) do_flags( debug, "Debug is now", "OFF", dbg );
      }
    return( 0 );
  }
