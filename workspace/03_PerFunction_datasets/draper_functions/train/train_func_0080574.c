bu_release_op(node * n) {
	op_info &oi = op_map[n];

	GCM_DUMP(
	sblog << "  bu release op  ";
	dump::dump_op(n);
	);

	nuc_stk[ucs_level].erase(n);
	pending.remove_node(n);

	bu_find_best_bb(n, oi);

	if (oi.bottom_bb == bu_bb) {
		GCM_DUMP( sblog << "   ready\n";);
		add_ready(n);
	} else {
		GCM_DUMP( sblog << "   ready_above\n";);
		ready_above.push_back(n);
	}
}
