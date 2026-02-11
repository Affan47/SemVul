execute( const MapCoordinate& pos, ContainerBase* subject, int num )
{
    if ( NewGuiHost::pendingCommand ) {
        delete NewGuiHost::pendingCommand;
        NewGuiHost::pendingCommand = NULL;
    }

    actmap->cleartemps(7);
    updateFieldInfo();
    displaymap();
}
