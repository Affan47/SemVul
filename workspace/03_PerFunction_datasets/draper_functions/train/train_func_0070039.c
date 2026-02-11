compute_max_error(const Point *d, int nd, const Bezier &b,
		  const Vector<double> &parameters, int *split_point)
{
    *split_point = nd/2;
    double max_dist = 0.0;
    for (int i = 1; i < nd - 1; i++) {
	double dist = (b.eval(parameters[i]) - d[i]).squared_length();
	if (dist >= max_dist) {
	    max_dist = dist;
	    *split_point = i;
	}
    }
    return max_dist;
}
