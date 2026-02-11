BuildTLWList( TLWList &list ) const {
  const UnitSet &us = mission.GetUnitSet();
  TLWListBuilder::BuildUnitTypesList( us, list );


  unsigned short maxw = container.MaxWeight();
  if ( container.IsUnit() )
    maxw = MIN( maxw, mission.StorageLeft(static_cast<Unit &>(container)) );

  TLWNode *n = static_cast<TLWNode *>(list.Head()), *n2;
  while ( n ) {

    const UnitType *ut = us.GetUnitInfo( n->ID() );
    if ( (ut->Weight() < container.MinWeight()) ||
         (ut->Weight() > maxw) ) {
      n2 = static_cast<TLWNode *>(n->Next());
      n->Remove();
      delete n;
      n = n2;
    } else n = static_cast<TLWNode *>(n->Next());
  }
}
