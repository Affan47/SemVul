socketGameTavernLord()
{
	uint idLord = _socket->readInt();
	AiLord * lord = new AiLord();
	lord->setId( idLord );
	_lordtav.append( lord );
	if(_player->numLord() < 2 ) {
		if(_player->canBuy(DataTheme.lords.at(idLord)) && !_basetav->isVisitorLord()) {
			int col = _basetav->getCell()->getCol();
			int row = _basetav->getCell()->getRow();
			_socket->sendLordBuy( lord , row, col);
		}
	}
}
