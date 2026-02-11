import_atoms(const FineAtoms& fa, OperationTree& otree, Tintintmap& tmap)
{
	StaticAtoms::import_atoms(fa, otree, tmap);


	const vector<const char*>& fa_params = fa.get_params();
	for (unsigned int i = 0; i < fa_params.size(); i++)
		register_param(fa_params[i]);


	const vector<const char*>& fa_endovars = fa.get_endovars();
	for (unsigned int i = 0; i < fa_endovars.size(); i++)
		register_endo(fa_endovars[i]);


	const vector<const char*>& fa_exovars = fa.get_exovars();
	for (unsigned int i = 0; i < fa_exovars.size(); i++)
		register_exo(fa_exovars[i]);

	parsing_finished();
}
