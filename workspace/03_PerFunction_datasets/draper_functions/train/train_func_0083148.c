sec_asn1d_get_enclosing_construct(sec_asn1d_state *state)
{
    for (state = state->parent; state; state = state->parent) {
	sec_asn1d_parse_place place = state->place;
	if (place != afterImplicit      &&
	    place != afterPointer       &&
	    place != afterInline        &&
	    place != afterSaveEncoding  &&
	    place != duringSaveEncoding &&
	    place != duringChoice) {


            break;
	}
    }
    return state;
}
