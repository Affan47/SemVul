CreateUnit( unsigned char type, Player &p,
     const Point &pos, Direction dir, unsigned char group, unsigned char xp ) {
  Unit *u;
  const UnitType *utype = unit_set.GetUnitInfo( type );

  if ( utype->Flags() & U_TRANSPORT )
    u = new Transport( utype, &p, CreateUnitID(), pos );
  else
    u = new Unit( utype, &p, CreateUnitID(), pos );

  u->Face( dir );
  u->SetGroupSize( group );
  u->AwardXP( xp * XP_PER_LEVEL );
  units.AddTail( u );
  map.SetUnit( u, pos );

  if ( history ) history->RecordUnitEvent( *u, History::HIST_UEVENT_CREATE );

  u->SetFlags( U_DONE );

  return u;
}
