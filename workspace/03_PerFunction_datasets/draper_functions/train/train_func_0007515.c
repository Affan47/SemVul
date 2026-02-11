calc3DColor(QColor &color, bool darken)
{
  int rb = color.red();
  int gb = color.green();
  int bb = color.blue();
  int a = color.alpha();

  int brightness_ = brightness(rb,gb,bb);

  int f0, f1;
  if (brightness_ < COLOR_DARK_THRESHOLD) {
    f0 = COLOR_DARK_BS_FACTOR;
    f1 = COLOR_DARK_TS_FACTOR;
  } else if (brightness_ > COLOR_LIGHT_THRESHOLD) {
    f0 = COLOR_LITE_BS_FACTOR;
    f1 = COLOR_LITE_TS_FACTOR;
  } else {
    f0 = COLOR_DARK_BS_FACTOR +
      (brightness_ *
       (COLOR_LITE_BS_FACTOR - COLOR_DARK_BS_FACTOR) / MAX_COLOR);
    f1 = COLOR_DARK_TS_FACTOR +
      (brightness_ *
       (COLOR_LITE_TS_FACTOR - COLOR_DARK_TS_FACTOR) / MAX_COLOR);
  }

  if (darken) {
    int r = rb - (f0 * rb / 100);
    int g = gb - (f0 * gb / 100);
    int b = bb - (f0 * bb / 100);
    if ((r == rb) && (g == gb) && (b == bb))
      color = (color == Qt::black) ? QColor(DARK_GRAY) : QColor(Qt::black);
    else
      color.setRgb(r, g, b);
  } else {
    int r = qMin(rb + (f1 * (MAX_COLOR - rb) / 100), 255);
    int g = qMin(gb + (f1 * (MAX_COLOR - gb) / 100), 255);
    int b = qMin(bb + (f1 * (MAX_COLOR - bb) / 100), 255);
    if ((r == rb) && (g == gb) && (b == bb))
      color = (color == Qt::white) ? QColor(LIGHT_GRAY) : QColor(Qt::white);
    else
      color.setRgb(r, g, b);
  }
  color.setAlpha(a);
}
