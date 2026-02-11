detachState( StateAp *state )
{

	while ( state->inRange.head != 0 ) {

		TransAp *trans = state->inRange.head;
		StateAp *fromState = trans->fromState;


		detachTrans( fromState, state, trans );


		fromState->transMap.remove( trans->lowKey );
		delete trans;
	}


	for ( TransMap::Iter trans = state->transMap; trans.lte(); trans++ ) {
		detachTrans( state, trans->value->toState, trans->value );
		delete trans->value;
	}


	state->transMap.empty();


	if ( state->stateBits & SB_ISFINAL )
		finStateSet.remove( state );
}
