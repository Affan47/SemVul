dragUnitToInnerContainer( Vehicle* draggedUnit, Vehicle* targetUnit ) {
         if ( !draggedUnit )
            return;

         if ( draggedUnit != targetUnit ) {
            if ( targetUnit && CargoMoveCommand::moveInAvail(draggedUnit, targetUnit) ) {
               auto_ptr<CargoMoveCommand> cargomove ( new CargoMoveCommand( draggedUnit ));
               cargomove->setMode( CargoMoveCommand::moveInwards );
               cargomove->setTargetCarrier( targetUnit );
               ActionResult res = cargomove->execute ( createContext( getContainer()->getMap() ));
               if ( res.successful() )
                  cargomove.release();
            } else {
               if ( container->getCarrier() && !targetUnit ) {
                  auto_ptr<CargoMoveCommand> cargomove ( new CargoMoveCommand( draggedUnit ));
                  cargomove->setMode( CargoMoveCommand::moveOutwards );
                  ActionResult res = cargomove->execute ( createContext( getContainer()->getMap() ));
                  if ( res.successful() )
                     cargomove.release();
               } else {

               }
            }
         }
         cargoChanged();
      }
