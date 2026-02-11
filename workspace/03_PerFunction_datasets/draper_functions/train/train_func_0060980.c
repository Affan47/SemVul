shadeplot(double f1(double), double f2(double),
		 double t_min, double t_max, unsigned int num_pts)
  {

    path boundary(f1, t_min, t_max, num_pts);
    path graph2(f2, t_min, t_max, num_pts);

    path right_edge(P(t_max, f1(t_max)), P(t_max, f2(t_max)));
    path  left_edge(P(t_min, f2(t_min)), P(t_min, f1(t_min)));

    boundary += right_edge;
    boundary -= graph2;
    boundary += left_edge;

    boundary.close().fill();
    boundary.draw();
  }
