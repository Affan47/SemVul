setresult( const Context& context )
{
   MapCoordinate target = _attackedbuilding->getPosition();

   GameAction* b = new ConsumeAmmo( _attackingunit, _attackingunit->typ->weapons.weapon[av.weapnum].getScalarWeaponType(), av.weapnum, _attackingunit->ammo[ av.weapnum ] - av.weapcount );
   b->execute ( context );

   _attackingunit->postAttack( false, context );

   GameAction* f = new InflictDamage( _attackingunit, av.damage - _attackingunit->damage );
   f->execute ( context );

   GameAction* g = new InflictDamage( _attackedbuilding, dv.damage - _attackedbuilding->damage  );
   g->execute ( context );
}
