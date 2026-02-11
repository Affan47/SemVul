go_bezier_spline_to_path (GOBezierSpline *sp)
{
	int i, j;
	GOPath *path = go_path_new ();
	go_path_move_to (path, sp->x[0], sp->y[0]);
	for (i = j = 1; i < sp->n; i++, j += 3)
		go_path_curve_to (path, sp->x[j], sp->y[j], sp->x[j+1], sp->y[j+1], sp->x[j+2], sp->y[j+2]);
	if (sp->closed) {
		go_path_curve_to (path, sp->x[j], sp->y[j], sp->x[j+1], sp->y[j+1], sp->x[0], sp->y[0]);
		go_path_close (path);
	}
	return path;
}
