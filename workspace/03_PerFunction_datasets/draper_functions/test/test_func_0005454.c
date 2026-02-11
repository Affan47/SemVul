sendExchangeBaseLordUnit( GenericLord * lord1, int unit1, GenericLord * lord2, int unit2, uchar direction )
{
	init( (uchar)SO_EXCH, (uchar)C_EXCH_UNIT );
	if( lord1 ) {
		appendChar( (uchar)lord1->getId() );
	} else {
		appendChar( (uchar)-1 );
	}
	appendChar( (uchar)unit1 );

	if( lord2 ) {
		appendChar( (uchar)lord2->getId() );
	} else {
		appendChar( (uchar)-1 );
	}
	appendChar( (uchar)unit2 );

	appendChar( (uchar)direction );
	send();
}
