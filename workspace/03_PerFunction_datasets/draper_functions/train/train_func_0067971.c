arcto(qreal x1, qreal y1, qreal x2, qreal y2, qreal r)
{
  if (! d->state.hasPoint)
    d->state.path.moveTo(d->state.point);
  QPointF p1(x1,y1);
  QPointF u = d->state.point - p1;
  QPointF v = QPointF(x2,y2) - p1;
  qreal s = u.x() * v.y() - u.y() * v.x();
  if (s == 0)
    {
      lineto(x1,y1);
    }
  else
    {
      qreal ulen = sqrt(u.x() * u.x() + u.y() * u.y());
      qreal vlen = sqrt(v.x() * v.x() + v.y() * v.y());
      u /= ulen;
      v /= vlen;
      s /= ulen * vlen;
      qreal c = u.x() * v.x() + u.y() * v.y();
      qreal aw = atan2(s, -c);
      qreal as = (s>0) ? atan2(-u.x(),u.y()) : atan2(u.x(),-u.y());
      aw *= 180.0 / M_PI;
      as *= 180.0 / M_PI;
      QPointF o = p1 + (u + v) * fabs(r / s);
      QRectF rect(o.x()-r, o.y()-r, 2*r, 2*r);
      d->state.path.arcTo(rect, -as, aw);
      d->state.point = d->state.path.currentPosition();
      d->state.hasPoint = true;
    }
}
