ho_pixbuf_draw_line (ho_pixbuf * m, const int x1, const int y1,
  const int x2, const int y2, const unsigned char red,
  const unsigned char green, const unsigned char blue)
{
  double x, step_x;
  double y, step_y;
  int x_start = x1;
  int x_end = x2;
  int y_start = y1;
  int y_end = y2;

  step_x = ((double) x2 - (double) x1) * ((double) x2 - (double) x1);
  step_y = ((double) y2 - (double) y1) * ((double) y2 - (double) y1);

  if (step_y > step_x)
  {

    if (y1 > y2)
    {
      x_start = x2;
      x_end = x1;
      y_start = y2;
      y_end = y1;
    }

    x = (double) x_start;
    step_x =
      ((double) x_end - (double) x_start) / ((double) y_end - (double) y_start);
    for (y = y_start; y <= y_end; y++)
    {
      (m->data)[(int) x * m->n_channels + (int) y * m->rowstride] = red;
      if (m->n_channels >= 3)
      {
        (m->data)[(int) x * m->n_channels + (int) y * m->rowstride + 1] = green;
        (m->data)[(int) x * m->n_channels + (int) y * m->rowstride + 2] = blue;
      }
      x += step_x;
    }
  }
  else
  {

    if (x1 > x2)
    {
      x_start = x2;
      x_end = x1;
      y_start = y2;
      y_end = y1;
    }

    y = (double) y_start;
    step_y =
      ((double) y_end - (double) y_start) / ((double) x_end - (double) x_start);
    for (x = x_start; x <= x_end; x++)
    {
      (m->data)[(int) x * m->n_channels + (int) y * m->rowstride] = red;
      if (m->n_channels >= 3)
      {
        (m->data)[(int) x * m->n_channels + (int) y * m->rowstride + 1] = green;
        (m->data)[(int) x * m->n_channels + (int) y * m->rowstride + 2] = blue;
      }
      y += step_y;
    }
  }

  return FALSE;
}
