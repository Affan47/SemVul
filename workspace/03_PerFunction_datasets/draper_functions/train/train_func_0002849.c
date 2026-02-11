calc_squared_distance_seg_point_normalized(float x1, float y1, float x2, float y2, float x2n, float y2n, float px, float py)
{

	float dotprod = (x2 - x1) * (px - x1) + (y2 - y1) * (py - y1);

	if (dotprod > 0 && dotprod < (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) {


		float distline = fabsf(((y1 - y2n) * px + (x2n - x1) * py + (x1 * y2n - x2n * y1)));
		return distline;
	} else {

		if (dotprod < 0) {
			return ((px - x1) * (px - x1) + (py - y1) * (py - y1));
		} else
		{
			return ((px - x2) * (px - x2) + (py - y2) * (py - y2));
		}
	}
}
