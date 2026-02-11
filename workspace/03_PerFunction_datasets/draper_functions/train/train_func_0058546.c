prepare_alu_group() {

	alu_group_tracker &rt = alu.grp();

	unsigned i1 = 0;

	PSC_DUMP(
		sblog << "prepare_alu_group: starting...\n";
		dump_group(rt);
	);

	ready.append_from(&alu.conflict_nodes);


	do {

		process_ready_copies();

		++i1;

		for (node_iterator N, I = ready.begin(), E = ready.end(); I != E;
				I = N) {
			N = I; ++N;
			node *n = *I;

			PSC_DUMP(
				sblog << "p_a_g: ";
				dump::dump_op(n);
				sblog << "\n";
			);


			unsigned cnt = try_add_instruction(n);

			if (!cnt)
				continue;

			PSC_DUMP(
				sblog << "current group:\n";
				dump_group(rt);
			);

			if (rt.inst_count() == ctx.num_slots) {
				PSC_DUMP( sblog << " all slots used\n"; );
				break;
			}
		}

		if (!check_interferences())
			break;


		if (rt.has_ar_load() && alu.total_slots() > 121)
			break;

		if (rt.inst_count() && i1 > 50)
			break;

		regmap = prev_regmap;

	} while (1);

	PSC_DUMP(
		sblog << " prepare_alu_group done, " << rt.inst_count()
	          << " slot(s) \n";

		sblog << "$$$$$$$$PAG i1=" << i1
				<< "  ready " << ready.count()
				<< "  pending " << pending.count()
				<< "  conflicting " << alu.conflict_nodes.count()
				<<"\n";

	);

	return rt.inst_count();
}
