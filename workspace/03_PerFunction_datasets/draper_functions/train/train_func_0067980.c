dwc2_set_param_uframe_sched(struct dwc2_hsotg *hsotg, int val)
{
	if (DWC2_OUT_OF_BOUNDS(val, 0, 1)) {
		if (val >= 0) {
			dev_err(hsotg->dev,
				"'%d' invalid for parameter uframe_sched\n",
				val);
			dev_err(hsotg->dev, "uframe_sched must be 0 or 1\n");
		}
		val = 1;
		dev_dbg(hsotg->dev, "Setting uframe_sched to %d\n", val);
	}

	hsotg->core_params->uframe_sched = val;
}
