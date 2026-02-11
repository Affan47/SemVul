makeFirstSets()
{

	bool modified = true;
	while ( modified ) {
		modified = false;
		for ( DefList::Iter prod = prodList; prod.lte(); prod++ ) {
			if ( prod->fsm->startState->isFinState() ) {
				long *inserted = prod->firstSet.insert( -1 );
				if ( inserted != 0 )
					modified = true;
			}

			bool lmod = makeFirstSetProd( prod, prod->fsm->startState );
			if ( lmod )
				modified = true;
		}
	}


}
