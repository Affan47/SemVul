encode_atom(Erl_Atom_data* a, unsigned char **ext)
{
    int ix = 0;
    if (a->latin1) {
	ei_encode_atom_len_as((char*)*ext, &ix, a->latin1, a->lenL,
			      ERLANG_LATIN1, ERLANG_LATIN1);
    }
    else if (ei_encode_atom_len_as((char*)*ext, &ix, a->utf8, a->lenU,
				   ERLANG_UTF8, ERLANG_LATIN1) < 0) {
	ei_encode_atom_len_as((char*)*ext, &ix, a->utf8, a->lenU,
			      ERLANG_UTF8, ERLANG_UTF8);
    }
    *ext += ix;
}
