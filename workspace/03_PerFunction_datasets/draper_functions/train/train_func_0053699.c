proc_str (PLStream *pls, EscText *args)
{
  PLFLT *t = args->xform;
  PLFLT a1, alpha, ft_ht, angle, ref;
  PLDev *dev = (PLDev *) pls->dev;
  PLINT clxmin, clxmax, clymin, clymax;
  int jst, font;


  ft_ht = pls->chrht * 72.0/25.4;


  angle = pls->diorot * 90.;
  a1 = acos(t[0]) * 180. / PI;
  if (t[2] > 0.)
    alpha = a1 - angle;
  else
    alpha = 360. - a1 - angle;

  alpha = alpha * PI / 180.;


  difilt(&args->x, &args->y, 1, &clxmin, &clxmax, &clymin, &clymax);


  if ( args->x < clxmin || args->x > clxmax || args->y < clymin || args->y > clymax)
    return;


  if (args->just == 0.5)
    jst = 1;
  else if (args->just == 1.)
    jst = 2;
  else {
    jst = 0;
    args->x = args->refx;
    args->y = args->refy;
  }


  if (args->base == 2)
    ref = - DPI/72. * ft_ht / 2.;
  else if (args->base == 1)
    ref = 0.;
  else
    ref = DPI/72. * ft_ht / 2.;


  args->y = offset + dev->ymax * (int)dev->xscale_dev - (args->y - ref*cos(alpha));
  args->x = args->x + ref*sin(alpha);


  switch (pls->cfont) {
  case (1): font = 0; break;
  case (2): font = 1; break;
  case (3): font = 3; break;
  case (4): font = 4; break;
  default:  font = 0;
  }

  fprintf(pls->OutFile,"4 %d %d 50 0 %d %f %f 4 1 1 %d %d %s\\001\n",
	  jst, curcol, font, 1.8  * ft_ht, alpha, args->x, args->y, args->string);

}
