execute( const MapCoordinate& pos, ContainerBase* subject, int num )
{
   if ( !subject )
      return;

   Vehicle* veh = dynamic_cast<Vehicle*>(subject);
   if ( !veh )
      return;

   ASCString msg = "do you really want to " + getCommandName( parent.getContainer() ) + " this unit ?";

   if (choice_dlg( msg ,"~y~es","~n~o") == 1) {
      auto_ptr<RecycleUnitCommand> command ( new RecycleUnitCommand( parent.getContainer() ));
      command->setUnit( veh );
      ActionResult res = command->execute( createContext( parent.getContainer()->getMap() ));
      if ( res.successful() )
         command.release();
      else
         displayActionError( res );
      parent.cargoChanged();
   }
}
