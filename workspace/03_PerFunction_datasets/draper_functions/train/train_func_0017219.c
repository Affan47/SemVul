convert_phi(value* select, node* phi) {
	assert(phi->dst.size() == 1 || phi->src.size() == 2);

	value *d = phi->dst[0];
	value *v1 = phi->src[0];
	value *v2 = phi->src[1];

	assert(d);

	if (!d->is_any_gpr())
		return NULL;

	if (v1->is_undef()) {
		if (v2->is_undef()) {
			return NULL;
		} else {
			return sh.create_mov(d, v2);
		}
	} else if (v2->is_undef())
		return sh.create_mov(d, v1);

	alu_node* n = sh.create_alu();

	n->bc.set_op(ALU_OP3_CNDE_INT);
	n->dst.push_back(d);
	n->src.push_back(select);
	n->src.push_back(v1);
	n->src.push_back(v2);

	return n;
}
