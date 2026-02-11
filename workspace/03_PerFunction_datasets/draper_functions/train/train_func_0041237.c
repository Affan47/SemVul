add_gpr_array(unsigned gpr_start, unsigned gpr_count,
					   unsigned comp_mask) {
	unsigned chan = 0;
	while (comp_mask) {
		if (comp_mask & 1) {
			gpr_array *a = new gpr_array(
					sel_chan(gpr_start, chan), gpr_count);

			SB_DUMP_PASS( sblog << "add_gpr_array: @" << a->base_gpr
			         << " [" << a->array_size << "]\n";
			);

			gpr_arrays.push_back(a);
		}
		comp_mask >>= 1;
		++chan;
	}
}
