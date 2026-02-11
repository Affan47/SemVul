Line(const P& arg1, const P& arg2)
  {
    P dir(arg2-arg1);
    const double denom(norm(dir));

    if (EPIX_EPSILON < denom)
      {

	dir *= 1/denom;
	line(arg1-100*dir, arg1+100*dir, 0, cam().is_linear() ? 1 : 400);
      }
  }
