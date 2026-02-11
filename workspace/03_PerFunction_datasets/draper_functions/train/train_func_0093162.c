S_has_runtime_code(pTHX_ RExC_state_t * const pRExC_state,
		    char *pat, STRLEN plen)
{
    int n = 0;
    STRLEN s;

    for (s = 0; s < plen; s++) {
	if (n < pRExC_state->num_code_blocks
	    && s == pRExC_state->code_blocks[n].start)
	{
	    s = pRExC_state->code_blocks[n].end;
	    n++;
	    continue;
	}


	if (pat[s] == '(' && s+2 <= plen && pat[s+1] == '?' &&
	    (pat[s+2] == '{'
                || (s + 2 <= plen && pat[s+2] == '?' && pat[s+3] == '{'))
	)
	    return 1;
    }
    return 0;
}
