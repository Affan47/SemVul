gg_svg_parse_points (const char *str, int *points, double **p_x, double **p_y)
{

    char value[1024];
    char *p_out = value;
    const char *p_in = str;
    double x;
    double y;
    char xy = 'x';
    struct gg_svg_dyn_points dyn;

    dyn.points = 0;
    dyn.first = NULL;
    dyn.last = NULL;

    while (1)
      {

	  if (*p_in == '\0')
	    {

		*p_out = '\0';
		if (*value != '\0')
		  {
		      if (xy == 'y')
			{
			    y = atof (value);
			    gg_svg_add_point (&dyn, x, y);
			    xy = 'x';
			}
		      else
			  x = atof (value);
		  }
		break;
	    }
	  if (*p_in == '\n' || *p_in == ' ' || *p_in == '\t' || *p_in == '\r'
	      || *p_in == ',')
	    {

		*p_out = '\0';
		if (*value != '\0')
		  {
		      if (xy == 'y')
			{
			    y = atof (value);
			    gg_svg_add_point (&dyn, x, y);
			    xy = 'x';
			}
		      else
			  x = atof (value);
		  }
		if (*p_in == ',')
		    xy = 'y';
		p_out = value;
		p_in++;
		continue;
	    }
	  *p_out++ = *p_in++;
      }

    if (dyn.points > 0)
      {

	  int iv = 0;
	  struct gg_svg_dyn_point *p = dyn.first;
	  double *xx = malloc (sizeof (double) * dyn.points);
	  double *yy = malloc (sizeof (double) * dyn.points);
	  while (p)
	    {
		*(xx + iv) = p->x;
		*(yy + iv) = p->y;
		iv++;
		p = p->next;
	    }
	  *points = dyn.points;
	  *p_x = xx;
	  *p_y = yy;
      }
    else
      {

	  *points = 0;
	  *p_x = NULL;
	  *p_y = NULL;
      }

    gg_svg_free_dyn_points (&dyn);
}
