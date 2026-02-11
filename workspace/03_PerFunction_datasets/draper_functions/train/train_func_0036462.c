unreserve(alu_node* n) {
	unsigned nsrc = n->bc.op_ptr->src_count, i;
	unsigned trans = n->bc.slot == SLOT_TRANS;
	unsigned bs = n->bc.bank_swizzle;
	unsigned opt = !trans
			&& n->bc.src[0].sel == n->bc.src[1].sel
			&& n->bc.src[0].chan == n->bc.src[1].chan;

	for (i = 0; i < nsrc; ++i) {
		value *v = n->src[i];
		if (v->is_readonly())
			continue;
		if (i == 1 && opt)
			continue;
		unsigned cycle = bs_cycle(trans, bs, i);
		unreserve(cycle, n->bc.src[i].sel, n->bc.src[i].chan);
	}
}
