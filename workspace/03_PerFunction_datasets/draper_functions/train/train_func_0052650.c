knot_power_init(mode,mi)
int mode;
struct method_instance *mi;
{
  charge_attr = find_attribute(VERTEX,CHARGE_ATTR_NAME);


  exponent_param = lookup_global(KNOTPOWER_NAME);
  if ( exponent_param < 0 )
    { exponent_param = add_global(KNOTPOWER_NAME);
      globals(exponent_param)->value.real = 2.0;
      globals(exponent_param)->flags |=  ORDINARY_PARAM | RECALC_PARAMETER | ALWAYS_RECALC;
    }
  ke_power = globals(exponent_param)->value.real/2;
  ke_power_i = (int) ke_power;
  ke_power_flag = 0;
  if (ke_power<0.) return;
  ke_power_l = (int) (log(ke_power)/log(2.));
  if ( fabs(ke_power_l - log(ke_power)/log(2.)) < 1e-8  && ke_power_l <= 20)
    ke_power_flag = -1;
  else if ( fabs(ke_power_i - ke_power) < 1e-12 && ke_power <= 150)
    ke_power_flag = 1;
}
