substitute_for_term(int t, int i, int j)
{
	int mlead, mlag;
	model.termspan(t, mlead, mlag);
	if (mlead > 1) {
		info.num_subst_terms++;


		map<int,int> lagsubst;
		model.variable_shift_map(model.eqs.nulary_of_term(t), 1-mlead, lagsubst);
		int lagt = model.eqs.add_substitution(t, lagsubst);


		char name[100];
		sprintf(name, "AUXLD_%d_%d_%d", i, j, 1);
		model.atoms.register_uniq_endo(name);
		info.num_aux_variables++;
		const char* ss = model.atoms.get_name_storage().query(name);
		int auxt = model.eqs.add_nulary(name);
		model.eqs.add_formula(model.eqs.add_binary(ogp::MINUS, auxt, lagt));
		aux_map.insert(Tsubstmap::value_type(ss, lagt));


		for (int ll = 1; ll <= mlead-2; ll++) {

			sprintf(name, "AUXLD_%d_%d_%d(+1)", i, j, ll);
			int lastauxt_lead = model.eqs.add_nulary(name);

			sprintf(name, "AUXLD_%d_%d_%d", i, j, ll+1);
			model.atoms.register_uniq_endo(name);
			info.num_aux_variables++;
			ss = model.atoms.get_name_storage().query(name);
			auxt = model.eqs.add_nulary(name);

			model.eqs.add_formula(model.eqs.add_binary(ogp::MINUS, auxt, lastauxt_lead));


			aux_map.insert(Tsubstmap::value_type(ss, lagt));
		}


		model.substitute_atom_for_term(ss, +1, t);
	}
}
