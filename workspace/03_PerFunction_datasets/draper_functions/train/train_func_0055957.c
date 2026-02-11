fpga_switch_str_i(struct fpga_model* model, int y, int x,
	swidx_t swidx, int from_to)
{
	struct fpga_tile* tile;
	uint32_t sw;
	int connpt_o;

	tile = YX_TILE(model, y, x);
	sw = tile->switches[swidx];
	connpt_o = SW_I(sw, from_to);
	return tile->conn_point_names[connpt_o*2+1];
}
