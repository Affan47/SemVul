imode_activate (splotd * sp, ProjectionMode pmode, InteractionMode imode,
                gboolean state, ggobid * gg)
{
  displayd *display = (displayd *) sp->displayptr;
  cpaneld *cpanel = &display->cpanel;
  RedrawStyle redraw_style = NONE;

  if (state == off) {
    switch (imode) {
    case DEFAULT_IMODE:
      switch (pmode) {
      case P1PLOT:
        p1d_activate (state, display, gg);
        break;
      case XYPLOT:
        xyplot_activate (state, display, gg);
        break;
      case TOUR2D3:
        if (cpanel->t2d3.manip_mode != MANIP_OFF)
          splot_cursor_set ((gint) NULL, sp);
        break;
      case TOUR2D:
        if (cpanel->t2d.manip_mode != MANIP_OFF)
          splot_cursor_set ((gint) NULL, sp);
        break;
      case COTOUR:
        if (cpanel->tcorr.manip_mode != MANIP_OFF)
          splot_cursor_set ((gint) NULL, sp);
        break;
      case TOUR1D:
      case NULL_PMODE:
      case DEFAULT_PMODE:
      case EXTENDED_DISPLAY_PMODE:

      case N_PMODES:
        break;
      }
      break;
    case BRUSH:
      redraw_style = brush_activate (state, display, sp, gg);
      break;
    case IDENT:
      redraw_style = identify_activate (state, display, gg);
      break;
    case SCALE:
      splot_cursor_set ((gint) NULL, sp);

      disconnect_motion_signal (sp);

      break;
    case EDGEED:
      redraw_style = edgeedit_activate (state, display, gg);
      break;
    default:
      break;
    }
  }
  else if (state == on) {
    switch (imode) {
    case DEFAULT_IMODE:
      switch (pmode) {
      case P1PLOT:
        p1d_activate (state, display, gg);
        break;
      case XYPLOT:
        xyplot_activate (state, display, gg);
        break;
      case TOUR2D3:
        if (cpanel->t2d3.manip_mode != MANIP_OFF)
          splot_cursor_set (GDK_HAND2, sp);
        break;
      case TOUR2D:
        if (cpanel->t2d.manip_mode != MANIP_OFF)
          splot_cursor_set (GDK_HAND2, sp);
        break;
      case COTOUR:
        if (cpanel->tcorr.manip_mode != MANIP_OFF)
          splot_cursor_set (GDK_HAND2, sp);
        break;
      case TOUR1D:
      case NULL_PMODE:
      case DEFAULT_PMODE:
      case EXTENDED_DISPLAY_PMODE:
      case N_PMODES:
        break;
      }
      break;
    case BRUSH:
      redraw_style = brush_activate (state, display, sp, gg);
      break;
    case IDENT:
      redraw_style = identify_activate (state, display, gg);
      break;
    case SCALE:
      splot_cursor_set (GDK_HAND2, sp);
      break;
    case EDGEED:
      redraw_style = edgeedit_activate (state, display, gg);
      break;
    default:
      break;
    }
  }
  return redraw_style;
}
