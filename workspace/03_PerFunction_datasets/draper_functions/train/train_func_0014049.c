lalr1AddFollow1( TransAp *trans )
{
	StateAp *state = trans->fromState;
	int fkey = trans->lowKey;
	KlangEl *flel = langElIndex[fkey];
	if ( flel == 0 || flel->type == KlangEl::Term ) {

		for ( TransInList::Iter in = state->inRange; in.lte(); in++ ) {
			long key = in->lowKey;
			KlangEl *langEl = langElIndex[key];
			if ( langEl != 0 && langEl->type == KlangEl::NonTerm ) {

				long prior = trans->maxPrior();
				lalr1AddFollow2( in, fkey, prior );
			}
		}
	}
}
