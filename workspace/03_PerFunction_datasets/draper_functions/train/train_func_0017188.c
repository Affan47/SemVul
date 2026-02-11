get_space_for_curve()
{
	max_in_curve = INITIAL_CURVE_SIZE;
	if(curve_storage_exists) {
		gr_Error("storage is messed up (internal error)");
		return;
	}
	xcurve = new double [max_in_curve];
	ycurve = new double [max_in_curve];
	legitcurve = new bool [max_in_curve];
	curve_storage_exists = true;
	num_in_curve = 0;
}
