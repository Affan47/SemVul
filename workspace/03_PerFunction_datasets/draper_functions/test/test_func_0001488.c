set_bounds (float lb, float ub)
{
	if (_lower_bound != lb || _upper_bound != ub) {
		_lower_bound = lb;
		_upper_bound = ub;


		if (_value < _lower_bound) {
			_value = _lower_bound;
			update_value_str();
			Refresh(false);
		}
		else if (_value > _upper_bound) {
			_value = _upper_bound;
			update_value_str();
			Refresh(false);
		}
	}
}
