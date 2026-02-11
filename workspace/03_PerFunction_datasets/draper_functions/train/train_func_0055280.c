isPointNearOther(double x, double y) const {
	for (map<double,map<double,double> >::const_iterator x_it = this->field.lower_bound(x - this->max_used_distance); x_it != this->field.end(); x_it++) {
		double x_delta = x_it->first - x;
		if (x_delta > this->max_used_distance) break;

		for (map<double,double>::const_iterator y_it = x_it->second.lower_bound(y - this->max_used_distance); y_it != x_it->second.end(); y_it++) {
			double y_delta = y_it->first - y;
			if (y_delta > this->max_used_distance) break;

			if (sqrt(x_delta*x_delta + y_delta*y_delta) <= y_it->second) {
				return true;
			}
		}

	}

	return false;
}
