image(QRectF drect, QtLuaPainter *p, QRectF srect)
{
  Locker lock(this);
  d->p->drawImage(drect, p->image(), srect);
  d->damage(drect);
}
