pixmap(int f) const
{
  if ((f<0) || (f >= (int)_field.size()))
    return QPixmap();

  return _field[f].pix;
}
