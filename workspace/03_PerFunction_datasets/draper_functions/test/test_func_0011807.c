sqcurve_energy_string_init()
{
  curve_power_param = lookup_global(CURVE_POWER_NAME);
  if ( curve_power_param < 0 )
  { curve_power_param = add_global(CURVE_POWER_NAME);
    globals(curve_power_param)->value.real = 2.0;
    globals(curve_power_param)->flags |=  ORDINARY_PARAM;
  }
  curve_power = globals(curve_power_param)->value.real;
}
