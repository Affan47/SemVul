searchFields()
{
   if ( !getUnit() )
      return ActionResult(201);

   if (getUnit()->getMovement() < mineputmovedecrease)
      return ActionResult( 119 );


   objectsCreatable.clear();
   objectsRemovable.clear();

   if ( weaponNum >= 0 )
      circularFieldIterator( getMap(), getUnit()->getPosition(), getUnit()->typ->weapons.weapon[weaponNum].maxdistance/10, getUnit()->typ->weapons.weapon[weaponNum].mindistance/10, FieldIterationFunctor( this, &PutMineCommand::fieldChecker ));

   if ( objectsRemovable.size() + objectsCreatable.size() ) {
      setState(Evaluated);
      return ActionResult(0);
   } else
      return ActionResult(21504);
}
