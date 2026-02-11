vpip_scaled_real_to_time64(double val, struct __vpiScope*scope)
{
      int units;
      if (scope)
	    units = scope->time_units;
      else
	    units = vpi_time_precision;

      double scale = pow(10.0L, units - vpi_time_precision);
      val *= scale;

      return (vvp_time64_t) val;
}
