Load( MemBuffer &file, Mission &mission ) {
  unsigned short num_events = file.Read16();

  if ( num_events > 0 ) {
    unsigned short num_units, i;
    num_units = file.Read16();

    for ( i = 0; i < num_events; ++i ) {
      HistEvent *he = new HistEvent();
      he->Load( file );
      events.AddTail( he );
    }

    for ( i = 0; i < num_units; ++i ) {
      Unit *u = mission.LoadUnit( file, true );
      if ( u ) units.AddTail( u );
    }
  }
  return num_events;
}
