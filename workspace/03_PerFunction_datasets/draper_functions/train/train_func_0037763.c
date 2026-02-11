bind_cdev(struct thermal_cooling_device *cdev)
{
	int i, ret;
	const struct thermal_zone_params *tzp;
	struct thermal_zone_device *pos = NULL;

	mutex_lock(&thermal_list_lock);

	list_for_each_entry(pos, &thermal_tz_list, node) {
		if (!pos->tzp && !pos->ops->bind)
			continue;

		if (pos->ops->bind) {
			ret = pos->ops->bind(pos, cdev);
			if (ret)
				print_bind_err_msg(pos, cdev, ret);
			continue;
		}

		tzp = pos->tzp;
		if (!tzp || !tzp->tbp)
			continue;

		for (i = 0; i < tzp->num_tbps; i++) {
			if (tzp->tbp[i].cdev || !tzp->tbp[i].match)
				continue;
			if (tzp->tbp[i].match(pos, cdev))
				continue;
			tzp->tbp[i].cdev = cdev;
			__bind(pos, tzp->tbp[i].trip_mask, cdev,
			       tzp->tbp[i].binding_limits,
			       tzp->tbp[i].weight);
		}
	}

	mutex_unlock(&thermal_list_lock);
}
