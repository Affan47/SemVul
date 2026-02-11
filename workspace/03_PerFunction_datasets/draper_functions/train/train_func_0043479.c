sendLordVisit( GenericLord * lord, bool state )
{
	init( (uchar) SO_MODIF, (uchar)C_MOD_LORD, (uchar) C_LORD_VISIT );
	appendChar( lord->getOwner()->getNum() );
	appendInt( lord->getCell()->getRow() );
	appendInt( lord->getCell()->getCol() );
	appendChar( lord->getId() );
	if( state ) {
		appendChar( 1 );
	} else {
		appendChar( 0 );
	}
	send();
}
