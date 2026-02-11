q_facet_tension_u_init(mode,mi)
int mode;
struct method_instance *mi;
{
  if ( web.gauss2D_order < 5 )
     { web.gauss2D_order = 5; gauss_setup(); }
}
