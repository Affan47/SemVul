sec_asn1d_confirm_identifier (sec_asn1d_state *state)
{
    PRBool match;

    PORT_Assert (state->place == afterIdentifier);

    match = (PRBool)(((state->found_tag_modifiers & state->check_tag_mask)
	     == state->expect_tag_modifiers)
	    && ((state->found_tag_number & state->check_tag_mask)
		== state->expect_tag_number));
    if (match) {
	state->place = beforeLength;
    } else {
	if (state->optional) {
	    state->missing = PR_TRUE;
	    state->place = afterEndOfContents;
	} else {
	    PORT_SetError (SEC_ERROR_BAD_DER);
	    state->top->status = decodeError;
	}
    }
}
