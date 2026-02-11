parsing_finished()
{

	der_atoms.clear();
	endo_atoms_map.clear();
	exo_atoms_map.clear();


	for (unsigned int i = 0; i < endovars.size(); i++) {
		int t = index(endovars[i]);
		if (t != -1) {
			endo_atoms_map.push_back(der_atoms.size());
			der_atoms.push_back(t);
		}
	}
	for (unsigned int i = 0; i < exovars.size(); i++) {
		int t = index(exovars[i]);
		if (t != -1) {
			exo_atoms_map.push_back(der_atoms.size());
			der_atoms.push_back(t);
		}
	}
}
