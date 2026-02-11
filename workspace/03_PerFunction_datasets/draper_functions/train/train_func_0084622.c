percentagePixmap(int w, int h, int percent, QColor c, bool framed)
{
  int iw, ix1, ih, iy1, iy2;


  if (framed) {
    iw = w-2, ix1 = 1;
    ih = h-2, iy1 = 1, iy2 = h-2;
  }
  else {
    iw = w; ix1 = 0;
    ih = h; iy1 = 0; iy2 = h-1;
  }

  int filled = iw*percent/100+1;
  if (!framed) w=filled;
  if (w<3) return QPixmap();

  QPixmap pix(w, h);
  pix.fill(Qt::white);
  QPainter p(&pix);
  p.setPen(Qt::black);
  if (framed)
    p.drawRect(0, 0, w-1, h-1);


  p.setPen(Qt::NoPen);
  p.setBrush(c);
  p.drawRect(ix1, iy1, filled-1,ih-1);


  int lastY = ih-(filled*ih - iw*ih*percent/100);
  int lastX1 = ix1+filled-2 + ((lastY>1) ? 1: 0);
  int lastX2 = ix1+filled-2;


  p.setPen(c.light());
  p.drawLine(ix1, iy1, lastX1, iy1);
  p.drawLine(ix1, iy1, ix1, iy2);
  p.setPen(c.dark());
  p.drawLine(lastX1, iy1, lastX1, iy1+lastY);
  p.drawLine(lastX2, iy1+lastY, lastX2, iy2);
  p.drawLine(ix1+1, iy2, lastX2, iy2);

  return pix;
}
