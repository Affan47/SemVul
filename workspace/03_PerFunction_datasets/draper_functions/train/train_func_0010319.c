tan_field(double f1(double), double f2(double), double t_min,
		 double t_max, unsigned int num_pts)
  {
    const double step((t_max - t_min)/num_pts);
    double t(t_min);

    for (unsigned int i=0; i <= num_pts; ++i, t += step)
      arrow(P(f1(t), f2(t)), P(f1(t), f2(t)) +
	    step*P(deriv(f1, t), deriv(f2, t)));
  }
