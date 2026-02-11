Conic_To (FT_Vector *control,
	  FT_Vector *to,
	  FT_Raster  raster)
{
  TPoint *    top;
  TPos        y1, y2, y3, ymin, ymax;
  TPos	      x1, x2, x3, xmin, xmax;
  TDirection  state_bez;

  Push_Conic (RAS_VAR_  control, to);

  do {
    y1 = ras.arc[2].y;
    y2 = ras.arc[1].y;
    y3 = ras.arc[0].y;
    x1 = ras.arc[2].x;
    x2 = ras.arc[1].x;
    x3 = ras.arc[0].x;


    if ( y1 <= y3 ) {
      ymin = y1;
      ymax = y3;
    }
    else {
      ymin = y3;
      ymax = y1;
    }

    if ( x1 <= x3 ) {
      xmin = x1;
      xmax = x3;
    }
    else {
      xmin = x3;
      xmax = x1;
    }

    if ((ymax - ymin) >= (xmax - xmin)) {
      if (y2 < ymin || y2 > ymax) {

	Split_Conic (ras.arc);
	ras.arc += 2;
      }
      else if (y1 == y3) {

	ras.arc -= 2;
      }
      else {


	state_bez = y1 < y3 ? Ascending : Descending;


	if (state_bez == Ascending) {
	  if (Bezier_Up (RAS_VAR_  2, Split_Conic, ras.minY, ras.maxY))
	    goto Fail;
	}
	else
	  if (Bezier_Down (RAS_VAR_  2, Split_Conic, ras.minY, ras.maxY))
	    goto Fail;
      }
    }

    else {
      if (x2 < xmin || x2 > xmax) {

	Split_Conic (ras.arc);
	ras.arc += 2;
      }
      else if (x1 == x3) {

	ras.arc -= 2;
      }
      else {


	state_bez = x1 < x3 ? Ascending : Descending;


	if (state_bez == Ascending) {
	  if (Bezier_Right (RAS_VAR_  2, Split_Conic, ras.minX, ras.maxX))
	    goto Fail;
	}
	else
	  if (Bezier_Left (RAS_VAR_  2, Split_Conic, ras.minX, ras.maxX))
	    goto Fail;
      }
    }

  } while (ras.arc >= ras.arcs);

  ras.last.x = x3;
  ras.last.y = y3;

  top = ras.cursor;

  ENTER_POINT_CHECK(top, ras.last.x, ras.last.y, "conic");

  ras.cursor = top;

  return SUCCESS;

Fail:
  return FAILURE;
}
