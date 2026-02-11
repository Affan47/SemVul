socketModifBaseUnit()
{
	int row = _socket->readInt();
	int col = _socket->readInt();
	uchar pos = _socket->readChar();
	uchar race = _socket->readChar();
	uchar level = _socket->readChar();
	int number = _socket->readInt();

	if( _map->at( row, col )->getBase() ) {
		GenericBase * base = (GenericBase *)_map->at( row, col )->getBase();
		base->addUnit( pos, race, level, number );
	}
}
