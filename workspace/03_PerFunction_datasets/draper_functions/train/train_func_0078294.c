updateUnit( GenericPlayer * player,GenericLord * lord , int num)
{
	AttalPlayerSocket * socket = findSocket( player );

	if( lord  && socket) {
		if( player == lord->getOwner() ) {
			socket->sendLordUnit( lord , num );
		} else {

			socket->sendLordUnit( lord , num);
		}
	}
}
