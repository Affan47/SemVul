distance(x1, y1, x2, y2)
	 double          x1,
	                 y1,
	                 x2,
	                 y2;
{


	double          delta_x,
	                delta_y;
	double          distance,
	                total;


	if (x2 > x1) {


		delta_x = x2 - x1;
		if (y2 > y1) {
			delta_y = y2 - y1;
		} else {
			delta_y = y1 - y2;
		}
	} else {


		delta_x = x1 - x2;
		if (y2 > y1) {
			delta_y = y2 - y1;
		} else {
			delta_y = y1 - y2;
		}
	}

	delta_y = delta_y * delta_y;
	delta_x = delta_x * delta_x;

	total = delta_y + delta_x;

	distance = sqrt(total);

	return ((int) distance);
}
