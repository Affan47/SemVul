termspan(int t, int& mlead, int& mlag) const
{
	mlead = INT_MIN;
	mlag = INT_MAX;
	const unordered_set<int>& nul_terms = eqs.nulary_of_term(t);
	for (unordered_set<int>::const_iterator ni = nul_terms.begin();
		 ni != nul_terms.end(); ++ni) {
		if (!atoms.is_constant(*ni) &&
			(atoms.is_type(atoms.name(*ni), DynareDynamicAtoms::endovar) ||
			 atoms.is_type(atoms.name(*ni), DynareDynamicAtoms::exovar))) {
			int ll = atoms.lead(*ni);
			if (ll < mlag)
				mlag = ll;
			if (ll > mlead)
				mlead = ll;
		}
	}
}
