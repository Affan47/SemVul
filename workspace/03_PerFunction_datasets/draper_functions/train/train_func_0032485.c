getCategoryName( uchar num )
{
	QString ret = _max;

	if( num < _list.count() ) {
		ret = _list.at( num )->getCategory();
	}

	return ret;
}
