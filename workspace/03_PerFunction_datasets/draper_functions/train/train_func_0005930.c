visit(cf_node& n, bool enter) {
	if (enter) {

		id = n.bc.id << 1;

		if ((n.bc.op_ptr->flags & CF_ALU) && n.bc.is_alu_extended()) {
			dump_dw(id, 2);
			id += 2;
			sblog << "\n";
		}

		dump_dw(id, 2);
		dump(n);

		if (n.bc.op_ptr->flags & CF_CLAUSE) {
			id = n.bc.addr << 1;
			new_group = 1;
		}
	}
	return true;
}
