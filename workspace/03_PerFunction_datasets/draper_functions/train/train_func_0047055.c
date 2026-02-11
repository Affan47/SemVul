schedule_alu(container_node *c) {

	assert(!ready.empty() || !ready_copies.empty());

	while (1) {

		prev_regmap = regmap;

		if (!prepare_alu_group()) {
			if (alu.current_ar) {
				emit_load_ar();
				continue;
			} else
				break;
		}

		if (!alu.check_clause_limits()) {
			regmap = prev_regmap;
			emit_clause();
			init_globals(live, false);
			continue;
		}

		process_group();
		alu.emit_group();
	};

	if (!alu.is_empty()) {
		emit_clause();
	}

	if (!ready.empty()) {
		sblog << "##post_scheduler: unscheduled ready instructions :";
		dump::dump_op_list(&ready);
		assert(!"unscheduled ready instructions");
	}

	if (!pending.empty()) {
		sblog << "##post_scheduler: unscheduled pending instructions :";
		dump::dump_op_list(&pending);
		assert(!"unscheduled pending instructions");
	}
}
