init( GenericBase * base )
{
	_base = base;

	for( int i = 0; i < MAX_UNIT; i++ ) {
		_troop[i]->init (_base->getUnit (i));
	}
}
