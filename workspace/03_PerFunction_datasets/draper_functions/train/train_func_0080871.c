getNeighbour1( GenericFightCell * cell )
{
	int row = cell->getRow();
	int col = cell->getCol();
	GenericFightCell * ret = 0;

	if ( _horizontalDraw )
	{
		if( row > 0 ) {
			ret = at( row - 1, col );
		}
	}
	else
	{
		if ( !isEven ( row ) )
		{
			if (( row > 0 ) && ( col < _width - 1 ))
			{
				ret = at ( row - 1, col + 1 );
			}
		}
		else if ( row > 0 )
		{
			ret = at ( row - 1, col );
		}
	}

	return ret;
}
