emit_load_ar() {

	regmap = prev_regmap;
	alu.discard_current_group();

	alu_group_tracker &rt = alu.grp();
	alu_node *a = alu.create_ar_load();

	if (!rt.try_reserve(a)) {
		sblog << "can't emit AR load : ";
		dump::dump_op(a);
		sblog << "\n";
	}

	alu.current_ar = 0;
}
