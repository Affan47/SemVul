startLinear(QPointF end, double velocity)
{
  mStart          = QPointF(x()/getScale(), y()/getScale());
  mEnd            = end;
  QPointF p       = mEnd-mStart;
  double dist     = sqrt(p.x()*p.x()+p.y()*p.y());
  if (dist > 0.0) mDuration = dist/velocity*1000.0;
  else mDuration = 0.0;
  mMovementState = LinearMove;
  mTime.restart();
  show();
}
