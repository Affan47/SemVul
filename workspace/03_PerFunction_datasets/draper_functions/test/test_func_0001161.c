fpga_swset_fromto(struct fpga_model* model, int y, int x,
	str16_t start_switch, int from_to, struct sw_set* set)
{
	swidx_t idx;

	RC_CHECK(model);
	set->len = 0;
	idx = fpga_switch_first(model, y, x, start_switch, from_to);
	while (idx != NO_SWITCH) {
		if (set->len >= SW_SET_SIZE)
			{ HERE(); return 0; }
		set->sw[set->len++] = idx;
		idx = fpga_switch_next(model, y, x, idx, from_to);
	}
	return 0;
}
