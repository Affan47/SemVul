plan(unsigned tests) throw(fatal_exception) {
		if (is_planned) {
			bail_out("Can't plan again!");
		}
		is_planned = true;
		output_plan(tests);
		expected = tests;
	}
