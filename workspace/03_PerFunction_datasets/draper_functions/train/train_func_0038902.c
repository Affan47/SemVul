cargoUnitMove( GameMap* actmap, int unitID, int targetContainerID )
{
   if ( !actmap )
      return ActionResult( 23500 );

   Vehicle* unit = actmap->getUnit( unitID );
   if ( !unit )
      return ActionResult(120);

   auto_ptr<CargoMoveCommand> ac( new CargoMoveCommand(unit) );

   Vehicle* target = NULL;
   if ( targetContainerID != -1 ) {
      target = actmap->getUnit( targetContainerID );
      if ( !target )
         return ActionResult(23410);

      if ( !CargoMoveCommand::moveInAvail( unit, target ))
         return ActionResult(23411);

      ac->setMode( CargoMoveCommand::moveInwards );
      ac->setTargetCarrier( target );

   } else {
      if ( !CargoMoveCommand::moveOutAvail( unit ))
         return ActionResult(23411);

      ac->setMode( CargoMoveCommand::moveOutwards );
   }

   ActionResult res = ac->execute( createContext( actmap ) );
   if ( res.successful() )
      ac.release();

   return res;
}
