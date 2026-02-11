gr_missing(double x)
{

	if (_grMissingValueUsed) {

		if (_grMissingValue == 0.0)
			return (x == 0.0);
		if (x == _grMissingValue) {

			return true;
		}
		x = GRI_ABS(x - _grMissingValue);
		if (x < _grMissingValue_tolerance) {

			return true;
		} else {

			return false;
		}
	} else {

		return false;
	}
}
