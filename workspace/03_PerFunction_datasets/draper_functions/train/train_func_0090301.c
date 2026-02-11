visit(if_node& n, bool enter) {
	if (enter) {
		indent();
		dump_flags(n);
		sblog << "if " << *n.cond << "    ";
		dump_common(n);
		sblog << "   ";
		dump_live_values(n, true);

		indent();
		sblog <<"{\n";

		++level;
	} else {
		--level;
		indent();
		sblog << "} endif   ";
		dump_live_values(n, false);
	}
	return true;
}
