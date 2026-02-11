tick_check_preferred(struct clock_event_device *curdev,
				 struct clock_event_device *newdev)
{

	if (!(newdev->features & CLOCK_EVT_FEAT_ONESHOT)) {
		if (curdev && (curdev->features & CLOCK_EVT_FEAT_ONESHOT))
			return false;
		if (tick_oneshot_mode_active())
			return false;
	}


	return !curdev ||
		newdev->rating > curdev->rating ||
	       !cpumask_equal(curdev->cpumask, newdev->cpumask);
}
