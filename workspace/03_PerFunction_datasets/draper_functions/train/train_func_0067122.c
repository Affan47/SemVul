RemoveUnit( Unit *unit ) {
  if ( unit->IsDummy() ) unit->UnsetFlags( U_SHELTERED );
  else {

    UCNode *n = static_cast<UCNode *>( uc_units.Head() );

    while ( n ) {
      if ( n->uc_unit == unit ) {
        n->Remove();
        delete n;

        unit->UnsetFlags( U_SHELTERED );


        uc_slots_full -= unit->Unit::Weight();
        break;
      }
      n = static_cast<UCNode *>( n->Next() );
    }
  }
}
