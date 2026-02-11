cml_atom_parity_start (GsfXMLIn *xin, xmlChar const **attrs)
{
	CMLReadState *state = (CMLReadState *) xin->user_state;
	if (attrs)
		while (*attrs) {
			if (!strcmp (reinterpret_cast < char const * > (*attrs), "atomRefs4")) {
				attrs++;
				state->curstr =  reinterpret_cast < char const * > (*attrs);
			} else
				attrs++;
			attrs++;
		}

}
