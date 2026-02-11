assign_variable(const char* varname, int ll, int t)
{
	if (indices.end() != indices.find(t))
		throw ogu::Exception(__FILE__,__LINE__,
							 "Attempt to assign already allocated tree index");

	Tvarmap::iterator it = vars.find(varname);
	if (it != vars.end()) {
		Tlagmap& lmap = (*it).second;
		if (lmap.end() != lmap.find(ll))
			throw ogu::Exception(__FILE__,__LINE__,
								 "Attempt to assign already allocated variable");
		lmap.insert(Tlagmap::value_type(ll, t));
	} else {
		Tlagmap lmap;
		lmap.insert(Tlagmap::value_type(ll, t));
		vars.insert(Tvarmap::value_type(varname, lmap));
	}
	indices.insert(Tindexmap::value_type(t, varname));

	nv++;
	if (ll < minlag)
		minlag = ll;
	if (ll > maxlead)
		maxlead = ll;
}
