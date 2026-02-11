gravity_init(mode,mi)
int mode;
struct method_instance *mi;
{

  if ( gravity_quantity_num >= 0 )
     GEN_QUANT(gravity_quantity_num)->modulus =
         web.gravflag ? web.grav_const : 0.0;
}
