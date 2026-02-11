init_area_weights (struct GRD_HEADER *G, GMT_LONG mode, float *A)
{


	GMT_LONG row, col, ij;
	double row_weight, col_weight, dy_half = 0.0, dx, y, lat, lat_s, lat_n, s2 = 0.0;

	if (mode) {
		if (mode == 5) dy_half = 0.5 * G->y_inc;
		dx = G->x_inc * R2D;
		s2 = sind (0.5 * G->y_inc);
	}
	else
		dx = G->x_inc;
	for (row = 0; row < G->ny; row++) {
		if (mode == 5) {
			y = GMT_j_to_y (row, G->y_min, G->y_max, G->y_inc, G->xy_off, G->ny);
			lat = IMG2LAT (y);
			lat_s = IMG2LAT (y - dy_half);
			lat_n = IMG2LAT (y + dy_half);
			row_weight = sind (lat_n) - sind (lat_s);
		}
		else if (mode) {
			lat = GMT_j_to_y (row, G->y_min, G->y_max, G->y_inc, G->xy_off, G->ny);
			if (fabs (lat) == 90.0)
				row_weight = 1.0 - cosd (0.5 * G->y_inc);
			else {
				row_weight = 2.0 * cosd (lat) * s2;

			}
		}
		else {
			row_weight = (G->node_offset == 0 && (row == 0 || row == (G->ny-1))) ? 0.5 : 1.0;
			row_weight *= G->y_inc;
		}

		for (col = 0, ij = row * G->nx; col < G->nx; col++, ij++) {
			col_weight = dx * ((G->node_offset == 0 && (col == 0 || col == (G->nx-1))) ? 0.5  : 1.0);
			A[ij] = (float)(row_weight * col_weight);
		}
	}
}
