execute(  const MapCoordinate& pos, ContainerBase* subject, int num )
{

    ConstructUnitCommand* construct = dynamic_cast<ConstructUnitCommand*>(NewGuiHost::pendingCommand);
    if ( !construct  ) {
        delete construct;
        auto_ptr<ConstructUnitCommand> constructCommand ( new ConstructUnitCommand( subject ));
        constructCommand->setMode( ConstructUnitCommand::external);
        ConstructUnitCommand::Producables buildables = constructCommand->getProduceableVehicles();

        VehicleProduction_SelectionWindow fsw( NULL, PG_Rect( 10, 10, 450, 550 ), subject, buildables, false );
        fsw.Show();
        fsw.RunModal();
        const VehicleType* v = fsw.getVehicletype();
        if ( v ) {

            for ( ConstructUnitCommand::Producables::const_iterator i = buildables.begin(); i != buildables.end(); ++i )
                if ( i->type == v ) {
                    if ( i->prerequisites.getValue() & ( ConstructUnitCommand::Lack::Energy  | ConstructUnitCommand::Lack::Material | ConstructUnitCommand::Lack::Fuel )) {
                        warningMessage("Not enough resources to build unit");
                        return;
                    }

                    if ( i->prerequisites.getValue() & ( ConstructUnitCommand::Lack::Movement )) {
                        ASCString message = "Not enough movement to build unit";
                        Vehicle* constructor = dynamic_cast<Vehicle*>(subject);
                        if ( constructor )
                            message += "\nRequired: " + ASCString::toString(constructor->typ->unitConstructionMoveCostPercentage * constructor->maxMovement() / 100 ) + " points";
                        warningMessage(message);
                        return;
                    }

                    if ( i->prerequisites.getValue() & ( ConstructUnitCommand::Lack::Research )) {
                        warningMessage("This unit has not been researched yet");
                        return;
                    }
                }


            constructCommand->setVehicleType( v );
            vector<MapCoordinate> fields = constructCommand->getFields();

            if ( fields.size() ) {
                for ( vector<MapCoordinate>::const_iterator i = fields.begin(); i != fields.end(); ++i )
                    subject->getMap()->getField( *i )->a.temp = 1;

                repaintMap();

                NewGuiHost::pendingCommand = constructCommand.release();

                updateFieldInfo();

            } else {
                warningMessage("no fields to construct unit.\n" + v->terrainaccess.toString());
            }
        }
    } else {
        actmap->cleartemps();
        construct->setTargetPosition( pos );
        ActionResult res = construct->execute ( createContext( actmap ) );
        if ( !res.successful() ) {
            delete NewGuiHost::pendingCommand;
            repaintMap();
            dispmessage2( res );
        }
        NewGuiHost::pendingCommand = NULL;
        updateFieldInfo();
    }

}
