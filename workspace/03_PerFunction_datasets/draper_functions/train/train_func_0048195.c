execute( const MapCoordinate& pos, ContainerBase* subject, int num )
{
   if ( !subject )
      return;

   Vehicle* veh = dynamic_cast<Vehicle*>(subject);
   if ( !veh )
      return;

   auto_ptr<TrainUnitCommand> tuc ( new TrainUnitCommand( parent.getContainer() ));
   tuc->setUnit( veh );
   ActionResult res = tuc->execute( createContext( veh->getMap()));
   if ( res.successful() ) {
      tuc.release();
      parent.cargoChanged();
   } else
      displayActionError( res );
}
