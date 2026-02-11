handleMove( GenericFightUnit * unit, GenericFightCell * cell )
{

	TRACE("FightEngine::handleMove cell access %d, row %d , col %d", cell->getAccess(), cell->getRow(), cell->getCol());

	if( unit != _currentUnit ) {
		logEE( "The unit moving is not active !!" );
		return;
	}

	GenericFightCell* neib = NULL;


	if ( unit->getCreature()->getSize () == 2 ){

		neib = _map->getHeadCell( cell , unit->isLookingToRight() );

		if( ! _map->areNeighbours( unit->getCell(), cell ) &&  ! _map->areNeighbours( neib, cell )) {
			logEE( "The dest cell is not a neighbour cell of the unit" );
			printStatus( unit , cell );
			return;
		}
	} else {

		if( ! _map->areNeighbours( unit->getCell(), cell ) ) {
			logEE( "The dest cell is not a neighbour cell of the unit" );
			printStatus( unit , cell );
			return;
		}
	}

	switch( cell->getAccess() ) {
	case AttalCommon::UNKNOWN_ACCESS:
		logEE( "Should not happen (UNKNOWN_ACCESS)" );
		break;
	case AttalCommon::NEAR_FREE:
		TRACE("NEAR_FREE");
		moveUnit( unit, cell );
		break;
	case AttalCommon::NEAR_OCCUPIED:
		{
			TRACE("NEAR_OCCUPIED");
			GenericFightUnit * cellUnit = cell->getUnit();
			if( cellUnit ){
				if( cellUnit != unit){
					fightUnit( unit, cellUnit, ATTACK_FIGHT );
				} else if( neib ) {
					cellUnit = neib->getUnit();
					if( cellUnit ){
						if( cellUnit != unit){
							fightUnit( unit, cellUnit, ATTACK_FIGHT );
						}
					}
				}
			} else {
				logEE("NEAR_OCCUPIED Signal error, correct bug \n");
			}
		}
		break;
	case AttalCommon::FAR_FREE:
		logEE( "Should not happen (AttalCommon::FAR_FREE)" );
		printStatus( unit , cell );
		break;
	case AttalCommon::FAR_OCCUPIED:
		logEE( "Should not happen (FAR_OCCUPIED)" );
		printStatus( unit , cell );
		break;
	case AttalCommon::NONE:
		logEE( "Should not happen (NONE)" );
		printStatus( unit , cell );
		break;
	default:
		logEE( "Should not happen" );
		printStatus( unit , cell );
		break;
	}
}
