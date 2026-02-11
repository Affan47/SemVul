sendPlayerResource( GenericPlayer * player ,char ressource, int nb )
{
	AttalPlayerSocket * socket = findSocket( player );
	if( socket ) {
		if( DataTheme.resources.get( ressource )->isGlobal() ) {
			socket->sendPlayerResource( ressource, nb );
		}
	}
}
