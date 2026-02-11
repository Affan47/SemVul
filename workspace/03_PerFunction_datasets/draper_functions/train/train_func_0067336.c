InsertUnit( Unit *unit ) {
  short rc = 0;

  UCNode *n = new UCNode( unit );
  if ( n ) {
    unit->SetFlags( U_SHELTERED );
    uc_units.AddTail( n );

    if ( dynamic_cast<MapObject *>(this)->Owner() != unit->Owner() ) rc = 1;


    if ( unit->IsTransport() ) {
      Transport *t = static_cast<Transport *>(unit);

      SetCrystals( Crystals() + t->Crystals() );
      t->SetCrystals( 0 );

      while ( Unit *u = t->GetUnit(0) ) {
        t->RemoveUnit( u );
        InsertUnit( u );
      }
    }

    uc_slots_full += unit->Weight();
  } else rc = -1;
  return rc;
}
