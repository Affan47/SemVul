throb_blob (struct blob *b)
{
  int i;
  double frac = ((M_PI+M_PI) / b->npoints);

  for (i = 0; i < b->npoints; i++)
    {
      long r = b->r[i];
      long ra = (r > 0 ? r : -r);
      double th = (b->th > 0 ? b->th : -b->th);
      long x, y;


      x = b->x + ra * cos (i * frac + th);
      y = b->y + ra * sin (i * frac + th);

      b->spline->control_x[i] = x / SCALE;
      b->spline->control_y[i] = y / SCALE;


      ra += (RAND(b->elasticity) * (r > 0 ? 1 : -1));
      r = ra * (r >= 0 ? 1 : -1);


      if ((ra > b->max_r && r >= 0) ||
	  (ra < b->min_r && r < 0))
	r = -r;

      else if (! (random() % 50))
	r = -r;

      b->r[i] = r;
    }
}
