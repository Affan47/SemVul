drawShape(QPainter &p)
{
  if (Q3CanvasRectangle::visible())
    p.drawPixmap((int) x(), (int) y(), *m_pixmap);
}
