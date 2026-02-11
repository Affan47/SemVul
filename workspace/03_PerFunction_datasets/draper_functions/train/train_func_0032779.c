thermal_of_populate_bind_params(struct device_node *np,
					   struct __thermal_bind_params *__tbp,
					   struct thermal_trip *trips,
					   int ntrips)
{
	struct of_phandle_args cooling_spec;
	struct device_node *trip;
	int ret, i;
	u32 prop;


	__tbp->usage = THERMAL_WEIGHT_DEFAULT;
	ret = of_property_read_u32(np, "contribution", &prop);
	if (ret == 0)
		__tbp->usage = prop;

	trip = of_parse_phandle(np, "trip", 0);
	if (!trip) {
		pr_err("missing trip property\n");
		return -ENODEV;
	}


	for (i = 0; i < ntrips; i++)
		if (trip == trips[i].np) {
			__tbp->trip_id = i;
			break;
		}

	if (i == ntrips) {
		ret = -ENODEV;
		goto end;
	}

	ret = of_parse_phandle_with_args(np, "cooling-device", "#cooling-cells",
					 0, &cooling_spec);
	if (ret < 0) {
		pr_err("missing cooling_device property\n");
		goto end;
	}
	__tbp->cooling_device = cooling_spec.np;
	if (cooling_spec.args_count >= 2) {
		__tbp->min = cooling_spec.args[0];
		__tbp->max = cooling_spec.args[1];
	} else {
		pr_err("wrong reference to cooling device, missing limits\n");
	}

end:
	of_node_put(trip);

	return ret;
}
