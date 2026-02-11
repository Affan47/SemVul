setRate(double new_rate)
{
  rate = std::max(-1.0, std::min(1.0, new_rate));
  int r, g, b;
  if (rate > 0.0)
    positive.getRgb(&r, &g, &b);
  else
    negative.getRgb(&r, &g, &b);

  const double p = std::abs(rate);
  r = static_cast<int>(r*p + 255*(1-p));
  g = static_cast<int>(g*p + 255*(1-p));
  b = static_cast<int>(b*p + 255*(1-p));
  QPalette palette;
  palette.setColor(QPalette::Window, QColor(r, g, b));
  setPalette(palette);
  setAutoFillBackground(true);
}
