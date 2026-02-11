decrease( int nb )
{
	_nb -= nb;
	if( _nb < 0 ) {
		_nb = 0;
	}
}
