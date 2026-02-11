circular_arc_length_init(mode,mi)
int mode;
struct method_instance *mi;
{
  if ( (web.modeltype == LAGRANGE) && (web.lagrange_order >= 2) )
    kb_error(3371,"circular_arc_length method needs LINEAR or QUADRATIC model.\n",RECOVERABLE);
  circular_arc_flag = 1;
}
