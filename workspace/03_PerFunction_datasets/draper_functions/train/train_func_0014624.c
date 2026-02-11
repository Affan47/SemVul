checkData ( )
{

   if ( weaponShots.size() < unit->typ->weapons.count ) {
      size_t oldsize = weaponShots.size();
      weaponShots.resize( unit->typ->weapons.count );
      for ( size_t i = oldsize; i < unit->typ->weapons.count; ++i )
         weaponShots[i] = unit->typ->weapons.weapon[i].reactionFireShots;
   }
}
