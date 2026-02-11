makeNonTermFirstSetProd( Definition *prod, StateAp *state )
{
	bool modified = false;
	for ( TransMap::Iter trans = state->transMap; trans.lte(); trans++ ) {
		if ( trans->key >= firstNonTermId ) {
			long *inserted = prod->nonTermFirstSet.insert( trans->key );
			if ( inserted != 0 )
				modified = true;

			bool hasEpsilon = false;
			KlangEl *lel = langElIndex[trans->key];
			for ( LelDefList::Iter ldef = lel->defList; ldef.lte(); ldef++ ) {
				for ( ProdIdSet::Iter pid = ldef->nonTermFirstSet;
						pid.lte(); pid++ )
				{
					if ( *pid == -1 )
						hasEpsilon = true;
					else {
						long *inserted = prod->nonTermFirstSet.insert( *pid );
						if ( inserted != 0 )
							modified = true;
					}
				}
			}

			if ( hasEpsilon ) {
				if ( trans->value->toState->isFinState() ) {
					long *inserted = prod->nonTermFirstSet.insert( -1 );
					if ( inserted != 0 )
						modified = true;
				}

				bool lmod = makeNonTermFirstSetProd( prod, trans->value->toState );
				if ( lmod )
					modified = true;
			}
		}
	}
	return modified;
}
