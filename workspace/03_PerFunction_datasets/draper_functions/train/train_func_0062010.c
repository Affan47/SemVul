pid_controller(struct thermal_zone_device *tz,
			  int control_temp,
			  u32 max_allocatable_power)
{
	s64 p, i, d, power_range;
	s32 err, max_power_frac;
	u32 sustainable_power;
	struct power_allocator_params *params = tz->governor_data;

	max_power_frac = int_to_frac(max_allocatable_power);

	if (tz->tzp->sustainable_power) {
		sustainable_power = tz->tzp->sustainable_power;
	} else {
		sustainable_power = estimate_sustainable_power(tz);
		estimate_pid_constants(tz, sustainable_power,
				       params->trip_switch_on, control_temp,
				       true);
	}

	err = control_temp - tz->temperature;
	err = int_to_frac(err);


	p = mul_frac(err < 0 ? tz->tzp->k_po : tz->tzp->k_pu, err);


	i = mul_frac(tz->tzp->k_i, params->err_integral);

	if (err < int_to_frac(tz->tzp->integral_cutoff)) {
		s64 i_next = i + mul_frac(tz->tzp->k_i, err);

		if (abs(i_next) < max_power_frac) {
			i = i_next;
			params->err_integral += err;
		}
	}


	d = mul_frac(tz->tzp->k_d, err - params->prev_err);
	d = div_frac(d, tz->passive_delay);
	params->prev_err = err;

	power_range = p + i + d;


	power_range = sustainable_power + frac_to_int(power_range);

	power_range = clamp(power_range, (s64)0, (s64)max_allocatable_power);

	trace_thermal_power_allocator_pid(tz, frac_to_int(err),
					  frac_to_int(params->err_integral),
					  frac_to_int(p), frac_to_int(i),
					  frac_to_int(d), power_range);

	return power_range;
}
