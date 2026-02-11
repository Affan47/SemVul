cmyk(double c, double m, double y, double k)
  {
    the_paint_style().line_color(CMYK(c, m, y, k));
    the_paint_style().fill_color(CMYK(c, m, y, k));
    the_label_style().text_color(CMYK(c, m, y, k));
  }
