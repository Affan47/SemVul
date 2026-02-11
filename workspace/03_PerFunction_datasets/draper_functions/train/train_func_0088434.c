CommandUnitConquer( Unit *u, AIObj &obj ) {
  Unit *enemy;

  if ( u->IsConquer() ) {

    UnitGoTo( u, obj.pos, 0 );
  } else {

    enemy = FindBestTarget( u );
    if ( enemy && UnitGoTo( u, enemy->Position(), u->WeaponRange(enemy) ) ) {
      if ( u->CanHit( enemy ) ) mission.RegisterBattle( u, enemy );
    } else if ( !enemy ) CommandUnitReturnToBase( u );
  }
}
