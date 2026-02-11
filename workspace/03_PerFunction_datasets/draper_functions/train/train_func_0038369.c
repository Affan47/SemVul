h_axis_log_labels(const P& tail, const P& head,
			 const P& offset, epix_label_posn POSN,
			 unsigned int base)
  {
    if (EPIX_EPSILON < (tail.x2() - head.x2()) )
      return;

    const double my_y(tail.x2());


    const int k_lo((int)  ceil(min(tail.x1(), head.x1())));
    const int k_hi((int) floor(max(tail.x1(), head.x1())));

    h_axis_log_labels(P(k_lo, my_y), P(k_hi, my_y), k_hi - k_lo,
		      offset, POSN, base);
  }
