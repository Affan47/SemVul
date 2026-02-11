do_smooth_curve_to (GooCanvasPathCommand    *cmd,
		    GooCanvasPathCommandType prev_cmd_type,
		    cairo_t                 *cr,
		    gdouble                 *x,
		    gdouble                 *y,
		    gdouble                 *last_control_point_x,
		    gdouble                 *last_control_point_y)
{
  gdouble x1, y1;


  if (prev_cmd_type == GOO_CANVAS_PATH_CURVE_TO
      || prev_cmd_type == GOO_CANVAS_PATH_SMOOTH_CURVE_TO)
    {
      x1 = *x + (*x - *last_control_point_x);
      y1 = *y + (*y - *last_control_point_y);
    }
  else
    {
      x1 = *x;
      y1 = *y;
    }

  if (cmd->curve.relative)
    {
      cairo_curve_to (cr, x1, y1, *x + cmd->curve.x2, *y + cmd->curve.y2,
		      *x + cmd->curve.x, *y + cmd->curve.y);
      *last_control_point_x = *x + cmd->curve.x2;
      *last_control_point_y = *y + cmd->curve.y2;
      *x += cmd->curve.x;
      *y += cmd->curve.y;
    }
  else
    {
      cairo_curve_to (cr, x1, y1, cmd->curve.x2, cmd->curve.y2,
		      cmd->curve.x, cmd->curve.y);
      *last_control_point_x = cmd->curve.x2;
      *last_control_point_y = cmd->curve.y2;
      *x = cmd->curve.x;
      *y = cmd->curve.y;
    }
}
