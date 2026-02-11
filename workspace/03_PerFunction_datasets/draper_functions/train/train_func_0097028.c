updateStatusBar( GenericCell * c )
{
	if( c ) {
		QString msg;

		msg = tr( "(Cell %1x%2)" ).arg( c->getRow()).arg( c->getCol() );
		emit sig_status( msg );
	}
}
