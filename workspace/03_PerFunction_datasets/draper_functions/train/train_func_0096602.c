ei_internal_get_atom(const char** bufp, char* p,
			 erlang_char_encoding* was_encp)
{
    int ix = 0;
    if (ei_decode_atom_as(*bufp, &ix, p, MAXATOMLEN_UTF8, ERLANG_UTF8, was_encp, NULL) < 0)
	return -1;
    *bufp += ix;
    return 0;
}
