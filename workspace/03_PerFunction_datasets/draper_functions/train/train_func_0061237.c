visit(alu_packed_node& n, bool enter) {
	if (enter) {
		for (node_iterator I = n.begin(), E = n.end(); I != E; ++I) {
			I->accept(*this, true);
		}
	} else {
		for (node_iterator I = n.begin(), E = n.end(); I != E; ++I) {
			I->accept(*this, false);
		}

		bool repl = (n.op_ptr()->flags & AF_REPL) ||
				(ctx.is_cayman() && (n.first->alu_op_slot_flags() & AF_S));

		n.init_args(repl);
	}
	return false;
}
