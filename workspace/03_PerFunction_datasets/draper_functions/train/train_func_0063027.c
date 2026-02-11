cml_bond_start (GsfXMLIn *xin, xmlChar const **attrs)
{
	CMLReadState *state = (CMLReadState *) xin->user_state;
	Object *obj = state->app->CreateObject ("bond", state->cur.top ());
	if (obj) {
		map <string, unsigned>::iterator it;
		if (attrs)
			while (*attrs) {
				if ((it = KnownProps.find ((char const *) *attrs)) != KnownProps.end ()) {
					attrs++;
					obj->SetProperty ((*it).second, (char const *) *attrs);
				} else if (!strcmp ((char const *) *attrs, "atomRefs2")) {
					attrs++;
					char **atom_ids = g_strsplit ((char const *) *attrs, " ", 2);
					obj->SetProperty (GCU_PROP_BOND_BEGIN, atom_ids[0]);
					obj->SetProperty (GCU_PROP_BOND_END, atom_ids[1]);
					g_strfreev (atom_ids);
				} else
					attrs++;
				attrs++;
			}
	}
	state->cur.push (obj);
	state->doc->ObjectLoaded (obj);
}
