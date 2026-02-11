fpga_switch_search(struct fpga_model* model, int y, int x,
	swidx_t last, swidx_t search_beg, int from_to)
{
	struct fpga_tile* tile;
	int connpt_o, name_i, i;

	RC_CHECK(model);
	tile = YX_TILE(model, y, x);
	if (last & FIRST_SW) {
		connpt_o = fpga_connpt_find(model, y, x, last & ~FIRST_SW,
			 0,  0);
		if (connpt_o == NO_CONN) { HERE(); return NO_SWITCH; }
	} else
		connpt_o = SW_I(tile->switches[last], from_to);
	name_i = tile->conn_point_names[connpt_o*2+1];

	for (i = search_beg; i < tile->num_switches; i++) {
		connpt_o = SW_I(tile->switches[i], from_to);
		if (tile->conn_point_names[connpt_o*2+1] == name_i)
			break;
	}
	return (i >= tile->num_switches) ? NO_SWITCH : i;
}
