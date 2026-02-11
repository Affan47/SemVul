check_interferences() {

	alu_group_tracker &rt = alu.grp();

	unsigned interf_slots;

	bool discarded = false;

	PSC_DUMP(
			sblog << "check_interferences: before: \n";
	dump_regmap();
	);

	do {

		interf_slots = 0;

		for (unsigned s = 0; s < ctx.num_slots; ++s) {
			alu_node *n = rt.slot(s);
			if (n) {
				if (!unmap_dst(n)) {
					return true;
				}
			}
		}

		for (unsigned s = 0; s < ctx.num_slots; ++s) {
			alu_node *n = rt.slot(s);
			if (n) {
				if (!map_src(n)) {
					interf_slots |= (1 << s);
				}
			}
		}

		PSC_DUMP(
				for (unsigned i = 0; i < 5; ++i) {
					if (interf_slots & (1 << i)) {
						sblog << "!!!!!! interf slot: " << i << "  : ";
						dump::dump_op(rt.slot(i));
						sblog << "\n";
					}
				}
		);

		if (!interf_slots)
			break;

		PSC_DUMP( sblog << "ci: discarding slots " << interf_slots << "\n"; );

		rt.discard_slots(interf_slots, alu.conflict_nodes);
		regmap = prev_regmap;
		discarded = true;

	} while(1);

	PSC_DUMP(
		sblog << "check_interferences: after: \n";
		dump_regmap();
	);

	return discarded;
}
