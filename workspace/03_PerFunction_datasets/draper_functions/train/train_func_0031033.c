metric_area_init(mode,mi)
int mode;
struct method_instance *mi;
{  if ( web.conformal_flag || !web.metric_flag )
     kb_error(1583,"Cannot use metric_facet_area or metric_edge_length method without a general metric.\n",
      RECOVERABLE);
}
