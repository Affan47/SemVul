fill_2d_triangle(vector3* v, vector3 tri_color, vector3 slope, vector3 normal)
{
	vector3 final_color = get_color(tri_color, normal);

	vector3 sorted_v[3];
	sorted_v[0] = v[0];
	sorted_v[1] = v[1];
	sorted_v[2] = v[2];

	std::sort(sorted_v, sorted_v + 3, compare_y());

	vector3& a(sorted_v[0]);
	vector3& b(sorted_v[1]);
	vector3& c(sorted_v[2]);

	double min_x = min(a.x(), b.x(), c.x());
	double max_x = max(a.x(), b.x(), c.x());

	double dx1, dx2, dx3;
	if (b.y()-a.y() > 0) dx1=(b.x()-a.x())/(b.y()-a.y()); else dx1=0;
	if (c.y()-a.y() > 0) dx2=(c.x()-a.x())/(c.y()-a.y()); else dx2=0;
	if (c.y()-b.y() > 0) dx3=(c.x()-b.x())/(c.y()-b.y()); else dx3=0;

	double y_start = a.y();
	double y_mid = b.y();
	double y_stop = c.y();

	for(double y = y_start; y <= y_mid; y += 1)
	{
		double dy = y - a.y();
		double x1 = a.x() + dy * dx1;
		double x2 = a.x() + dy * dx2;
		horz_line(x1, x2, y, min_x, max_x, final_color, slope);
	}

	for(double y = y_mid; y <= y_stop; y += 1)
	{
		double dy = y - a.y();
		double x1 = b.x() + (y - b.y()) * dx3;
		double x2 = a.x() + dy * dx2;
		horz_line(x1, x2, y, min_x, max_x, final_color, slope);
	}


}
