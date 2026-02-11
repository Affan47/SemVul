GMT_check_lattice (double *x_inc, double *y_inc, GMT_LONG *pixel, GMT_LONG *active)
{


	if (!GMT_grd_info.active) return;


	if (!active || *active == FALSE) {
		*x_inc = GMT_grd_info.grd.x_inc;
		*y_inc = GMT_grd_info.grd.y_inc;
	}
	if (pixel) {

		*pixel = (*pixel) ? !GMT_grd_info.grd.node_offset : GMT_grd_info.grd.node_offset;
	}
	if (active) *active = TRUE;
}
