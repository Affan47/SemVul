goo_canvas_polyline_reconfigure_arrows (GooCanvasPolyline *polyline)
{
  GooCanvasItemSimple *simple = (GooCanvasItemSimple*) polyline;
  GooCanvasPolylineData *polyline_data = polyline->polyline_data;
  double line_width;

  if (!polyline_data->reconfigure_arrows)
    return;

  polyline_data->reconfigure_arrows = FALSE;

  if (polyline_data->num_points < 2
      || (!polyline_data->start_arrow && !polyline_data->end_arrow))
    return;

  line_width = goo_canvas_item_simple_get_line_width (simple);
  ensure_arrow_data (polyline_data);

  if (polyline_data->start_arrow)
    reconfigure_arrow (polyline_data, 0, 2, line_width,
		       polyline_data->arrow_data->line_start,
		       polyline_data->arrow_data->start_arrow_coords);

  if (polyline_data->end_arrow)
    {
      int end_point, prev_point;

      if (polyline_data->close_path)
	{
	  end_point = 0;
	  prev_point = polyline_data->num_points - 1;
	}
      else
	{
	  end_point = polyline_data->num_points - 1;
	  prev_point = polyline_data->num_points - 2;
	}

      reconfigure_arrow (polyline_data, end_point * 2, prev_point * 2,
			 line_width, polyline_data->arrow_data->line_end,
			 polyline_data->arrow_data->end_arrow_coords);
    }
}
