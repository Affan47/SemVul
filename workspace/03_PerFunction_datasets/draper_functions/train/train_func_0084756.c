dump_dot() {
	if(global_cfg.graph_out == NULL) return "";

	stringstream out;

	out << "digraph reaction_graph {" << endl;
	out << "   rankdir=LR;" << endl;


	out << "   node [shape = circle];" << endl;

	stringstream coda;

	out << "   N_" << root->hash << " [shape=ellipse, color=lightblue2, style=filled, label=\"" << root->bg->get_root(0)->to_string() << "\"];" << endl;

	for(set<node *>::iterator i = nodes.begin(); i!=nodes.end(); i++) {
		string rr = "root";

		string dc = "shape = ellipse, ";

		if((*i)->terminal)
			dc = "shape = doubleoctagon, ";

		out << "N_" << (*i)->hash << " [ " << dc << "label=\"" << (*i)->bg->get_root(0)->to_string() << "\"];" << endl;

		if((*i)->rule != NULL)
			rr = (*i)->rule->to_string();

		if((*i)->parent != NULL)
			out << "   N_" << (*i)->parent->hash << " -> N_" << (*i)->hash <<
				" [ label = \"" << rr << "\" ];" << endl;
	}

	out << coda.str();
	out << "}" << endl;

	FILE *fp = fopen(global_cfg.graph_out, "w");
	if(!fp) {
		cerr << "Error: could not open graph file " << global_cfg.graph_out << " for writing\n";
		return "";
	}

	fprintf(fp, "%s\n", out.str().c_str());

	fclose(fp);

	return out.str();


}
