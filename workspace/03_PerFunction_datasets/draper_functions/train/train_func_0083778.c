setresult( const Context& context )
{
   GameMap* map = _attackingunit->getMap();

   GameAction* b = new ConsumeAmmo( _attackingunit, _attackingunit->typ->weapons.weapon[av.weapnum].getScalarWeaponType(), av.weapnum, _attackingunit->ammo[ av.weapnum ] - av.weapcount );
   b->execute ( context );

   _attackingunit->postAttack( false, context );

   GameAction* f = new InflictDamage( _attackingunit, av.damage - _attackingunit->damage );
   f->execute ( context );


   MapCoordinate position( _x, _y );

   if ( dv.damage >= 100 ) {
      (new RemoveObject(map, position, _obji->typ->id))->execute(context);
   } else {
      GameAction* g = new ChangeObjectProperty( map, position, _obji, ChangeObjectProperty::Damage, dv.damage );
      g->execute ( context );
   }
}
