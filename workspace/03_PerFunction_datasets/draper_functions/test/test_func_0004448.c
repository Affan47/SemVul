multi_assign_network_signature( int what_kind )
{
	ushort sig;


	if ( what_kind == MULTI_SIG_SHIP ) {
		if ( Next_ship_signature < SHIP_SIG_MIN ){
			Next_ship_signature = SHIP_SIG_MIN;
		}

		sig = Next_ship_signature++;

		if ( Next_ship_signature == SHIP_SIG_MAX ) {
			Int3();
			Next_ship_signature = SHIP_SIG_MIN;
		}


	} else if ( what_kind == MULTI_SIG_ASTEROID ) {
		if ( Next_asteroid_signature < ASTEROID_SIG_MIN ){
			Next_asteroid_signature = ASTEROID_SIG_MIN;
		}

		sig = Next_asteroid_signature++;
		if ( Next_asteroid_signature == ASTEROID_SIG_MAX ) {
			Int3();
			Next_asteroid_signature = ASTEROID_SIG_MIN;
		}


	} else if ( what_kind == MULTI_SIG_DEBRIS ) {
		if ( Next_debris_signature < DEBRIS_SIG_MIN ){
			Next_debris_signature = DEBRIS_SIG_MIN;
		}

		sig = Next_debris_signature++;
		if ( Next_debris_signature == DEBRIS_SIG_MAX ) {
			Int3();
			Next_debris_signature = DEBRIS_SIG_MIN;
		}


	} else if ( what_kind == MULTI_SIG_NON_PERMANENT ) {
		if ( Next_non_perm_signature < NPERM_SIG_MIN ){
			Next_non_perm_signature = NPERM_SIG_MIN;
		}

		sig = Next_non_perm_signature++;
		if ( (Next_non_perm_signature < NPERM_SIG_MIN) || (Next_non_perm_signature == NPERM_SIG_MAX) ) {
			Next_non_perm_signature = NPERM_SIG_MIN;
		}
	} else {
		Int3();
		sig = 0;
	}

	return sig;
}
