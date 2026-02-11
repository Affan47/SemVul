grd_INSIDE (struct GRDMATH_INFO *info, float *stack[], GMT_LONG *constant, double *factor, GMT_LONG last)

{
	void grd_INSIDE_GEO (struct GRDMATH_INFO *info, float *stack[], GMT_LONG *constant, double *factor, GMT_LONG last);
	void grd_INSIDE_XY (struct GRDMATH_INFO *info, float *stack[], GMT_LONG *constant, double *factor, GMT_LONG last);

	if (GMT_io.in_col_type[0] & GMT_IS_GEO)
		grd_INSIDE_GEO (info, stack, constant, factor, last);
	else
		grd_INSIDE_XY (info, stack, constant, factor, last);
}
