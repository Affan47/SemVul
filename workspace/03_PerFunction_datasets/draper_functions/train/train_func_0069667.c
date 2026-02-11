setBuilding2Player( int idBuild, int player )
{
	TRACE("GameData::setBuilding2Player idBuilding %d, player %d", idBuild, player );

	if( ( _players.count() > player  )) {
		GenericBuilding * build = getBuildingById( idBuild );

		if( build->getOwner() ) {
			build->getOwner()->removeBuilding( build );
		}

		if( _players.at( player ) ) {
			build->setOwner( _players.at( player ) );
			_players.at( player )->addBuilding( build );
		}
	}
}
