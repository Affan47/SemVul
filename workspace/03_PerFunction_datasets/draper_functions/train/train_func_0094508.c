G_distance_between_line_segments(double ax1, double ay1,
				 double ax2, double ay2,
				 double bx1, double by1,
				 double bx2, double by2)
{
    double ra, rb;
    double x, y;


    if (G_intersect_line_segments(ax1, ay1, ax2, ay2,
				  bx1, by1, bx2, by2, &ra, &rb, &x, &y) > 0)
	return 0.0;
    return
	min4(G_distance_point_to_line_segment(ax1, ay1, bx1, by1, bx2, by2),
	     G_distance_point_to_line_segment(ax2, ay2, bx1, by1, bx2, by2),
	     G_distance_point_to_line_segment(bx1, by1, ax1, ay1, ax2, ay2),
	     G_distance_point_to_line_segment(bx2, by2, ax1, ay1, ax2, ay2)
	);
}
