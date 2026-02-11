changeX(int newX)
{

  newX = int((newX/65535.0)*XY_WIDTH + XY_WIDTH/2);

  if ( x == newX ) return;

  if ( trace )
  {
    tracePoints.append(QPoint(x, y));
    if ( tracePoints.count() == MAX_POINTS )
      tracePoints.removeFirst();
  }

  x = newX;
  update();
}
