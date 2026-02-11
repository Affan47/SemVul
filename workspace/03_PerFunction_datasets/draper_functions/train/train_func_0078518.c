StrokePoint (tdmInteractor I, int x, int y, int flag, int s)
{
  DEFDATA(I, tdmZoomData) ;
  DEFPORT(I_PORT_HANDLE) ;
  int dx, dy, ax, ay ;

  ENTRY(("StrokePoint(0x%x, %d, %d)", I, x, y));

  if ((PDATA(btn) == 2) || (x == PDATA(px) && y == PDATA(py))) {
    EXIT(("btn == 2 or no movement"));
    return ;
  }

  PDATA(px) = x ;
  PDATA(py) = y ;
  y = YFLIP(y) ;

  x = x<0 ? 0 : (x>CDATA(w) ? CDATA(w) : x) ;
  y = y<0 ? 0 : (y>CDATA(h) ? CDATA(h) : y) ;


  dx = x - PDATA(cx) ;
  dy = y - PDATA(cy) ;
  ax = abs(dx) ;
  ay = abs(dy) ;

  _dxf_DRAW_ZOOMBOX(I, (void *)0, (float (*)[4])identity, 0) ;


  if ((dy >=  dx * CDATA(aspect) && dy >= -dx * CDATA(aspect)) ||
      (dy <= -dx * CDATA(aspect) && dy <=  dx * CDATA(aspect)))
    {
      PDATA(y1) = PDATA(cy) - ay ;
      PDATA(x1) = PDATA(cx) - ay / CDATA(aspect) ;

      PDATA(y2) = PDATA(y1) + 2 * ay ;
      PDATA(x2) = PDATA(x1) + 2 * ay / CDATA(aspect) ;
    }
  else
    {
      PDATA(x1) = PDATA(cx) - ax ;
      PDATA(y1) = PDATA(cy) - ax * CDATA(aspect) ;

      PDATA(x2) = PDATA(x1) + 2 * ax ;
      PDATA(y2) = PDATA(y1) + 2 * ax * CDATA(aspect) ;
    }

  _dxf_DRAW_ZOOMBOX(I, (void *)0, (float (*)[4])identity, 1) ;

  EXIT((""));
}
