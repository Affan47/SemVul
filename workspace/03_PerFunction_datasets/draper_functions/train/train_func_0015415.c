get_widget_xy(GtkWidget *win, GtkWidget *widget, int *rx, int *ry)
{
  if (!win && !widget)
    p_err("get_widget_xy err");


  GtkRequisition sz;
  gtk_widget_get_preferred_size(widget, NULL, &sz);
  int wx, wy;

  wx=wy=0;

  gtk_widget_translate_coordinates(widget, win,
         0, sz.height, &wx, &wy);

  gtk_widget_translate_coordinates(widget, win,
         0, sz.height, &wx, &wy);


  int win_x, win_y;

  gtk_window_get_position(GTK_WINDOW(win), &win_x, &win_y);
  int win_xl, win_yl;
  get_win_size(win, &win_xl, &win_yl);

  if (wx > win_xl)
    wx = win_xl;

  *rx = win_x + wx;
  *ry = win_y + wy;
  return wx;
}
