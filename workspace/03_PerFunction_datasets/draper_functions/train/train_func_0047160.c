RemoveUnit( Unit *u ) {
  Map &map = mission->GetMap();

  if ( !u->IsSheltered() ) {
    map.SetUnit( NULL, u->Position() );
    mwin->GetMapView()->UpdateHex( u->Position() );
  } else {
    MapObject *o = map.GetMapObject( u->Position() );
    if ( o ) {
      if ( o->IsUnit() ) static_cast<Transport *>( o )->RemoveUnit( u );
      else static_cast<Building *>(o)->RemoveUnit( u );
    }
  }
}
