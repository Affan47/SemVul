setresult( const Context& context )
{
   int nwid = _attackingunit->networkid;
   GameMap* map = _attackingunit->getMap();

   GameAction* a = new ChangeUnitProperty( _attackingunit, ChangeUnitProperty::Experience, av.experience );
   a->execute ( context );

   GameAction* b = new ConsumeAmmo( _attackingunit, _attackingunit->typ->weapons.weapon[av.weapnum].getScalarWeaponType(), av.weapnum, _attackingunit->ammo[ av.weapnum ] - av.weapcount );
   b->execute ( context );

   _attackingunit->postAttack( reactionfire, context );

   GameAction* c = new RegisterUnitRFTarget( map, nwid, av.weapnum, _attackedunit->networkid  );
   c->execute ( context );

   if ( _respond ) {
      GameAction* d = new ChangeUnitProperty( _attackedunit, ChangeUnitProperty::Experience, dv.experience );
      d->execute ( context );

      GameAction* e = new ConsumeAmmo( _attackedunit, _attackedunit->typ->weapons.weapon[dv.weapnum].getScalarWeaponType(), dv.weapnum, _attackedunit->ammo[ dv.weapnum ] - dv.weapcount );
      e->execute ( context );
   }

   GameAction* f = new InflictDamage( _attackingunit, av.damage - _attackingunit->damage );
   f->execute ( context );

   if( av.damage >= 100 )
      log ( _attackedunit, _attackingunit );

   if( dv.damage >= 100 )
      log ( _attackingunit, _attackedunit );

   GameAction* g = new InflictDamage( _attackedunit, dv.damage - _attackedunit->damage  );
   g->execute ( context );


   if ( av.damage >= 100 ) {
     *_pattackingunit = NULL;
   }


   if ( dv.damage >= 100 ) {
     *_pattackedunit = NULL;
   }
}
