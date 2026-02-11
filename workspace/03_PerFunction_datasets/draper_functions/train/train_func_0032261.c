fpga_find_conn(struct fpga_model* model, int search_y, int search_x,
	str16_t* pt, int target_y, int target_x, str16_t target_pt)
{
	struct fpga_tile* tile;
	int i, j, dests_end;

	RC_CHECK(model);
	tile = YX_TILE(model, search_y, search_x);
	for (i = 0; i < tile->num_conn_point_names; i++) {
		dests_end = (i < tile->num_conn_point_names-1)
			? tile->conn_point_names[(i+1)*2]
			: tile->num_conn_point_dests;
		for (j = tile->conn_point_names[i*2]; j < dests_end; j++) {
			if (tile->conn_point_dests[j*3] == target_x
			    && tile->conn_point_dests[j*3+1] == target_y
			    && tile->conn_point_dests[j*3+2] == target_pt) {
				*pt = tile->conn_point_names[i*2+1];
				return 0;
			}
		}
	}
	*pt = STRIDX_NO_ENTRY;
	return 0;

}
