addParam0( int val )
{
	delete _params[ 0 ];
	_params[ 0 ] = new int( val );
}
