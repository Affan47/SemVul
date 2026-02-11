_goo_canvas_style_init (void)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      goo_canvas_style_stroke_pattern_id = g_quark_from_static_string ("GooCanvasStyle:stroke_pattern");
      goo_canvas_style_fill_pattern_id = g_quark_from_static_string ("GooCanvasStyle:fill_pattern");
      goo_canvas_style_fill_rule_id = g_quark_from_static_string ("GooCanvasStyle:fill_rule");
      goo_canvas_style_operator_id = g_quark_from_static_string ("GooCanvasStyle:operator");
      goo_canvas_style_antialias_id = g_quark_from_static_string ("GooCanvasStyle:antialias");
      goo_canvas_style_line_width_id = g_quark_from_static_string ("GooCanvasStyle:line_width");
      goo_canvas_style_line_cap_id = g_quark_from_static_string ("GooCanvasStyle:line_cap");
      goo_canvas_style_line_join_id = g_quark_from_static_string ("GooCanvasStyle:line_join");
      goo_canvas_style_line_join_miter_limit_id = g_quark_from_static_string ("GooCanvasStyle:line_join_miter_limit");
      goo_canvas_style_line_dash_id = g_quark_from_static_string ("GooCanvasStyle:line_dash");
      goo_canvas_style_font_desc_id = g_quark_from_static_string ("GooCanvasStyle:font_desc");
      goo_canvas_style_hint_metrics_id = g_quark_from_static_string ("GooCanvasStyle:hint_metrics");

      initialized = TRUE;
    }
}
