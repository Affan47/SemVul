ggobi_renderer_cairo_line_type (GGobiRendererCairo * self, GdkGCValues * values)
{
#line 420 "ggobi-renderer-cairo.c"
#define __GOB_FUNCTION__ "GGobi:Renderer:Cairo::line_type"
#line 54 "renderer-cairo.gob"
	g_return_if_fail (self != NULL);
#line 54 "renderer-cairo.gob"
	g_return_if_fail (GGOBI_IS_RENDERER_CAIRO (self));
#line 426 "ggobi-renderer-cairo.c"
{
#line 56 "renderer-cairo.gob"

    cairo_line_cap_t cap = CAIRO_LINE_CAP_ROUND;
    cairo_line_join_t join = CAIRO_LINE_JOIN_ROUND;


    cairo_set_line_width(selfp->cairo, values->line_width+1);

    switch(values->cap_style) {
      case GDK_CAP_ROUND:
        cap = CAIRO_LINE_CAP_ROUND;
      break;
      case GDK_CAP_BUTT:
      case GDK_CAP_NOT_LAST:
        cap = CAIRO_LINE_CAP_BUTT;
      break;
      case GDK_CAP_PROJECTING:
        cap = CAIRO_LINE_CAP_SQUARE;
      break;
    }
    cairo_set_line_cap(selfp->cairo, cap);

    switch(values->join_style) {
      case GDK_JOIN_ROUND:
        join = CAIRO_LINE_JOIN_ROUND;
      break;
      case GDK_JOIN_MITER:
        join = CAIRO_LINE_JOIN_MITER;

      break;
      case GDK_JOIN_BEVEL:
        join = CAIRO_LINE_JOIN_BEVEL;
      break;
    }
    cairo_set_line_join(selfp->cairo, join);


  }}
