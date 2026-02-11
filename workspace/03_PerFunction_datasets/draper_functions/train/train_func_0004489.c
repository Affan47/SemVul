set_current_brush (gGraphContextPtr ctx)
{

    if (ctx->current_brush.is_solid_color)
      {

	  cairo_set_source_rgba (ctx->cairo, ctx->current_brush.red,
				 ctx->current_brush.green,
				 ctx->current_brush.blue,
				 ctx->current_brush.alpha);
      }
    else if (ctx->current_brush.is_linear_gradient)
      {

	  cairo_pattern_t *pattern =
	      cairo_pattern_create_linear (ctx->current_brush.x0,
					   ctx->current_brush.y0,
					   ctx->current_brush.x1,
					   ctx->current_brush.y1);
	  cairo_pattern_add_color_stop_rgba (pattern, 0.0,
					     ctx->current_brush.red,
					     ctx->current_brush.green,
					     ctx->current_brush.blue,
					     ctx->current_brush.alpha);
	  cairo_pattern_add_color_stop_rgba (pattern, 1.0,
					     ctx->current_brush.red2,
					     ctx->current_brush.green2,
					     ctx->current_brush.blue2,
					     ctx->current_brush.alpha2);
	  cairo_set_source (ctx->cairo, pattern);
	  cairo_pattern_destroy (pattern);
      }
    else if (ctx->current_brush.is_pattern)
      {

	  cairo_set_source (ctx->cairo, ctx->current_brush.pattern);
      }
}
