scatterplotMovePointsMotionCb (displayd * display, splotd * sp, GtkWidget * w,
                               GdkEventMotion * event, ggobid * gg)
{
  GGobiData *d = display->d;
  gboolean button1_p, button2_p;
  gboolean inwindow, wasinwindow;


  wasinwindow = mouseinwindow (sp);

  mousepos_get_motion (w, event, &button1_p, &button2_p, sp);
  inwindow = mouseinwindow (sp);

  if (gg->buttondown == 0) {

    gint k = find_nearest_point (&sp->mousepos, sp, d, gg);
    d->nearest_point = k;
    if (k != d->nearest_point_prev) {
      displays_plot (NULL, QUICK, gg);
      d->nearest_point_prev = k;
    }

  }
  else {


    if (inwindow) {

      if ((sp->mousepos.x != sp->mousepos_o.x) ||
          (sp->mousepos.y != sp->mousepos_o.y)) {


        if (d->nearest_point != -1) {
          move_pt (d->nearest_point, sp->mousepos.x, sp->mousepos.y,
                   sp, d, gg);
        }
        sp->mousepos_o.x = sp->mousepos.x;
        sp->mousepos_o.y = sp->mousepos.y;
      }
    }
    else {
      if (wasinwindow) {
        d->nearest_point = -1;
        splot_redraw (sp, QUICK, gg);
      }
    }
  }
}
