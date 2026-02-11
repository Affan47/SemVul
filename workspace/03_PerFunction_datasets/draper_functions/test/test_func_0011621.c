create_grid_objectiveCmd(double xr,
			 double yr,
			 const std::vector<double> &xgood,
			 const std::vector<double> &ygood,
			 const std::vector<double> &zgood)
{
	int             number_to_find = 5, enlargements = 1;
	double          xx, yy;
	if (_nword == 9) {
		if (!getinum(_word[7], &number_to_find)) {
			READ_WORD_ERROR(".n.");
			demonstrate_command_usage();
			return 0;
		}
		if (!getinum(_word[8], &enlargements)) {
			READ_WORD_ERROR(".e.");
			demonstrate_command_usage();
			return 0;
		}
	}

	if (!allocate_grid_storage(_num_xmatrix_data, _num_ymatrix_data)) {
		err("Insufficient space for matrix");
		return 0;
	}
	unsigned int i, j;
	unsigned int found = 0;

	for (i = 0; i < _num_xmatrix_data; i++)
		for (j = 0; j < _num_ymatrix_data; j++)
			_legit_xy(i, j) = false;

	bool warned = false;
	GriTimer t;
	for (i = 0; i < _num_xmatrix_data; i++) {
		double          fpred;
		xx = _xmatrix[i];
		for (j = 0; j < _num_ymatrix_data; j++) {
			int number_found;
			yy = _ymatrix[j];
			number_found = gr_grid1(xgood,
						ygood,
						zgood,
						xx,
						yy,
						xr,
						yr,
						2,
						number_to_find,
						enlargements,
						&fpred);
			_f_xy(i, j) = fpred;
			if (number_found >= (int) (GRI_ABS((double) number_to_find))) {
				_legit_xy(i, j) = true;
				found++;
			} else {
				_legit_xy(i, j) = false;
			}
		}
		if (!warned) {
			double frac = (i + 1.0) * _num_ymatrix_data;
			frac /= _num_xmatrix_data * _num_ymatrix_data;
			warned = warn_if_slow(&t, frac, "convert columns to grid");
		}
	}
	return found;
}
