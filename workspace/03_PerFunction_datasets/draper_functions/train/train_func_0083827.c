stpui_curve_set_curve_type (StpuiCurve *c, StpuiCurveType new_type)
{
  gfloat rx, dx;
  gint x, i;

  if (new_type != c->curve_type)
    {
      gint width, height;

      width  = GTK_WIDGET (c)->allocation.width - RADIUS * 2;
      height = GTK_WIDGET (c)->allocation.height - RADIUS * 2;

      if (new_type == STPUI_CURVE_TYPE_FREE)
	{
	  stpui_curve_interpolate (c, width, height);
	  c->curve_type = new_type;
	}
      else if (c->curve_type == STPUI_CURVE_TYPE_FREE)
	{
	  if (c->ctlpoint)
	    g_free (c->ctlpoint);
	  c->num_ctlpoints = 9;
	  c->ctlpoint = g_malloc (c->num_ctlpoints * sizeof (*c->ctlpoint));

	  rx = 0.0;
	  dx = (width - 1) / (gfloat) (c->num_ctlpoints - 1);

	  for (i = 0; i < c->num_ctlpoints; ++i, rx += dx)
	    {
	      x = (int) (rx + 0.5);
	      c->ctlpoint[i][0] =
		unproject (x, c->min_x, c->max_x, width);
	      c->ctlpoint[i][1] =
		unproject (RADIUS + height - c->point[x].y,
			   c->min_y, c->max_y, height);
	    }
	  c->curve_type = new_type;
	  stpui_curve_interpolate (c, width, height);
	}
      else
	{
	  c->curve_type = new_type;
	  stpui_curve_interpolate (c, width, height);
	}
      g_signal_emit (c, curve_type_changed_signal, 0);
      g_object_notify (G_OBJECT (c), "curve_type");
      stpui_curve_draw (c, width, height);
    }
}
