getValue( uint num )
{
	int ret = 0;

	if( (int)num < _list->count() ) {
		ret = _list->item( num )->text().toInt();
	}

	return ret;
}
