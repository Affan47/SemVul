set_options      (BarData *bar_data)
{

  annotate_set_rectifier (bar_data->rectifier);

  annotate_set_rounder (bar_data->rounder);

  annotate_set_thickness (bar_data->thickness);

  annotate_set_arrow (is_arrow_toggle_tool_button_active ());

  if (is_eraser_toggle_tool_button_active ())
    {
      annotate_select_eraser ();
    }
  else
    {
      annotate_set_color (bar_data->color);
      annotate_select_pen ();
    }

}
