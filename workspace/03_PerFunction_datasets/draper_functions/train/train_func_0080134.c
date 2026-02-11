try_add_instruction(node *n) {

	alu_group_tracker &rt = alu.grp();

	unsigned avail_slots = rt.avail_slots();

	if (n->is_alu_packed()) {
		alu_packed_node *p = static_cast<alu_packed_node*>(n);
		unsigned slots = p->get_slot_mask();
		unsigned cnt = __builtin_popcount(slots);

		if ((slots & avail_slots) != slots) {
			PSC_DUMP( sblog << "   no slots \n"; );
			return 0;
		}

		p->update_packed_items(ctx);

		if (!rt.try_reserve(p)) {
			PSC_DUMP( sblog << "   reservation failed \n"; );
			return 0;
		}

		p->remove();
		return cnt;

	} else {
		alu_node *a = static_cast<alu_node*>(n);
		value *d = a->dst.empty() ? NULL : a->dst[0];

		if (d && d->is_special_reg()) {
			assert(a->bc.op_ptr->flags & AF_MOVA);
			d = NULL;
		}

		unsigned allowed_slots = ctx.alu_slots_mask(a->bc.op_ptr);
		unsigned slot;

		allowed_slots &= avail_slots;

		if (!allowed_slots)
			return 0;

		if (d) {
			slot = d->get_final_chan();
			a->bc.dst_chan = slot;
			allowed_slots &= (1 << slot) | 0x10;
		} else {
			if (a->bc.op_ptr->flags & AF_MOVA) {
				if (a->bc.slot_flags & AF_V)
					allowed_slots &= (1 << SLOT_X);
				else
					allowed_slots &= (1 << SLOT_TRANS);
			}
		}


		if ((a->bc.op == ALU_OP3_MULADD || a->bc.op == ALU_OP3_MULADD_IEEE) &&
				!ctx.is_egcm()) {
			allowed_slots &= 0x0F;
		}

		if (!allowed_slots) {
			PSC_DUMP( sblog << "   no suitable slots\n"; );
			return 0;
		}

		slot = __builtin_ctz(allowed_slots);
		a->bc.slot = slot;

		PSC_DUMP( sblog << "slot: " << slot << "\n"; );

		if (!rt.try_reserve(a)) {
			PSC_DUMP( sblog << "   reservation failed\n"; );
			return 0;
		}

		a->remove();
		return 1;
	}
}
