slot_Center( int row, int col)
{
	if( _map->inMap( row, col )) {
		this->centerOn( col * DataTheme.tiles.getWidth(), row * DataTheme.tiles.getHeight() );
	}
}
