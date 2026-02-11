isPlaceBaseFree( int race , GenericCell * cell)
{
	if( cell ) {
		GenericBaseModel * baseModel = DataTheme.bases.at( race );
		int col = cell->getCol() - baseModel->getDoorCol();
		int row = cell->getRow() - baseModel->getDoorRow();
		for( uint i = 0; i < baseModel->getHeight(); i++ ) {
			for( uint j = 0; j < baseModel->getWidth(); j++ ) {
				if( baseModel->getDisposition( i, j ) == GenericMapDisposition::OCCUPIED ) {
					if( ( int( row + i ) >= 0 ) && ( int( col + j ) >= 0 )
					&& ( ( row + i ) < _height ) && ( ( col + j ) < _width ) ) {

						if(!_theCells[row+i][col+j]->isStoppable())
							return false;
					}
				}
			}
		}
	}
	return true;
}
