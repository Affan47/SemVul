execute(  const MapCoordinate& pos, ContainerBase* subject, int num )
{
    DestructBuildingCommand* dbc = dynamic_cast<DestructBuildingCommand*>( NewGuiHost::pendingCommand );
    if ( !dbc ) {
		Vehicle* unit = actmap->getField(pos)->vehicle;
		if ( !unit )
			return;

        auto_ptr<DestructBuildingCommand> db ( new DestructBuildingCommand( unit ));

        vector<MapCoordinate> fields = db->getFields();

        if ( fields.empty() ) {
            dispmessage2( 306, NULL );
            return;
        }
        for ( vector<MapCoordinate>::iterator i = fields.begin(); i != fields.end(); ++i )
            actmap->getField(*i)->a.temp = 1;

        repaintMap();

        NewGuiHost::pendingCommand = db.release();

        updateFieldInfo();

    } else {
        dbc->setTargetPosition( pos );
        actmap->cleartemps();

        ActionResult res = dbc->execute( createContext( actmap ));
        if ( !res.successful() ) {
            displayActionError(res);
            delete NewGuiHost::pendingCommand;
        }
        NewGuiHost::pendingCommand = NULL;

        repaintMap();
        updateFieldInfo();
    }
}
