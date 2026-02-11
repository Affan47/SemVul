analyzeMachine()
{
	maxState = graph->stateList.length() - 1;
	maxLelId = nextSymbolId - 1;
	maxOffset = graph->stateList.length() * maxLelId;

	for ( StateList::Iter state = graph->stateList; state.lte(); state++ ) {
		for ( TransMap::Iter trans = state->transMap; trans.lte(); trans++ ) {
			if ( trans->value->isShift ) {
				trans->value->actions.append( SHIFT_CODE );
				trans->value->actPriors.append( trans->value->shiftPrior );
			}
			for ( ReductionMap::Iter red = trans->value->reductions; red.lte(); red++ ) {
				trans->value->actions.append( makeReduceCode( red->key, false ) );
				trans->value->actPriors.append( red->value );
			}
			trans->value->actOrds.appendDup( 0, trans->value->actions.length() );
		}
	}

	long nextTime = computeActOrds();
	sortActions();
	advanceReductions( nextTime );
	graph->setStateNumbers();
	reduceActions();


	int actionSetId = 0;
	for ( ActionSet::Iter asi = actionSet; asi.lte(); asi++ )
		asi->key.id = actionSetId++;


	maxIndex = actionSetId - 1;


	maxProdLen = 0;
	for ( DefList::Iter prod = prodList; prod.lte(); prod++ ) {
		if ( (unsigned)prod->fsmLength > maxProdLen )
			maxProdLen = prod->fsmLength;
	}
}
