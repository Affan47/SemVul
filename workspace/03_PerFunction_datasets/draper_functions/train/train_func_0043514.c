set_samples()
{
    int tsamp1, tsamp2;

    c_token++;
    tsamp1 = abs(int_expression());
    tsamp2 = tsamp1;
    if (!END_OF_COMMAND) {
	if (!equals(c_token,","))
	    int_error(c_token, "',' expected");
	c_token++;
	tsamp2 = abs(int_expression());
    }
    if (tsamp1 < 2 || tsamp2 < 2)
	int_error(c_token, "sampling rate must be > 1; sampling unchanged");
    else {
	struct surface_points *f_3dp = first_3dplot;

	first_3dplot = NULL;
	sp_free(f_3dp);

	samples_1 = tsamp1;
	samples_2 = tsamp2;
    }
}
