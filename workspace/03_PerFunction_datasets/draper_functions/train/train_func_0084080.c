grdinfo (double info[], char *filein, struct GRD_HEADER *grd)
{


	if (info) {
		info[0] = grd->x_min;
		info[1] = grd->x_max;
		info[2] = grd->y_min;
		info[3] = grd->y_max;
		info[4] = grd->z_min;
		info[5] = grd->z_max;
		info[6] = grd->node_offset;
		info[7] = grd->x_inc;
		info[8] = grd->y_inc;
	}

	mexPrintf("%s: Title: %s\n", filein, grd->title);
	mexPrintf("%s: Command: %s\n", filein, grd->command);
	mexPrintf("%s: Remark: %s\n", filein, grd->remark);
	if (grd->node_offset)
		mexPrintf("%s: Pixel registration used\n", filein);
	else
		mexPrintf("%s: Normal node registration used\n", filein);
	mexPrintf("%s: x_min: %g x_max: %g x_inc: %g name: %s nx: %d\n",
		filein, grd->x_min, grd->x_max, grd->x_inc, grd->x_units, grd->nx);
	mexPrintf("%s: y_min: %g y_max: %g y_inc: %g name: %s ny: %d\n",
		filein, grd->y_min, grd->y_max, grd->y_inc, grd->y_units, grd->ny);
	mexPrintf("%s: z_min: %g z_max: %g name: %s\n",
		filein, grd->z_min, grd->z_max, grd->z_units);
	mexPrintf("%s: scale_factor: %g add_offset: %g\n",
		filein, grd->z_scale_factor, grd->z_add_offset);
}
