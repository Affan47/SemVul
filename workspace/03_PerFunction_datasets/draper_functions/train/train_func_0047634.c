init_group_literals(alu_group_node* g) {

	g->literals.clear();
	for (unsigned i = 0; i < 4; ++i) {
		if (!lt[i])
			break;

		g->literals.push_back(lt[i]);

		PSC_DUMP(
			sblog << "literal emitted: " << lt[i].f;
			sblog.print_zw_hex(lt[i].u, 8);
			sblog << "   " << lt[i].i << "\n";
		);
	}
}
