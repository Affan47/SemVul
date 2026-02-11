getCategoryNumber()
{
	uint ret = 0;

	if( _estimated ) {
		ret = _categoryNumber;
	} else {
		ret = (uchar)DataTheme.computeCategory( getCreatureNumber() );
	}

	return ret;
}
