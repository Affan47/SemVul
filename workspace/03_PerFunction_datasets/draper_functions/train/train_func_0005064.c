cml_scalar_start (GsfXMLIn *xin, G_GNUC_UNUSED xmlChar const **attrs)
{
	CMLReadState *state = (CMLReadState *) xin->user_state;
	state->curstr = "";
	state->proptype = "xsd:double";
	if (attrs)
		while (*attrs) {
			if (!strcmp (reinterpret_cast <char const *> (*attrs), "title") ||
			    !strcmp (reinterpret_cast <char const *> (*attrs), "dictRef")) {
				map <string, unsigned>::iterator it = KnownProps.find (reinterpret_cast <char const *> (attrs[1]));
			    state->cur_prop = it == KnownProps.end ()? static_cast <unsigned> (GCU_PROP_MAX): (*it).second;
			} else if (!strcmp (reinterpret_cast <char const *> (*attrs), "dataType"))
				state->proptype = reinterpret_cast <char const *> (attrs[1]);
			else if (!strcmp (reinterpret_cast <char const *> (*attrs), "units"))
				state->curstr = reinterpret_cast <char const *> (attrs[1]);
			attrs += 2;
		}
}
