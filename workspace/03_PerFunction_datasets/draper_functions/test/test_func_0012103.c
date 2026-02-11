arc(qreal x, qreal y, qreal r, qreal a1, qreal a2)
{
  QRectF rect(x-r, y-r, 2*r, 2*r);
  if (d->state.unit == Radians)
    {
      a1 *= 180 / M_PI;
      a2 *= 180 / M_PI;
    }
  if (a2 < a1)
    a2 += 360 * ceil((a1-a2)/360);
  if (!d->state.hasPoint)
    d->state.path.arcMoveTo(rect, -a1);
  d->state.path.arcTo(rect, -a1, a1-a2);
  d->state.point = d->state.path.currentPosition();
  d->state.hasPoint = true;
}
