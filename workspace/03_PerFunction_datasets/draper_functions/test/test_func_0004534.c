gen6_set_rps_thresholds(struct drm_i915_private *dev_priv, u8 val)
{
	int new_power;
	u32 threshold_up = 0, threshold_down = 0;
	u32 ei_up = 0, ei_down = 0;

	new_power = dev_priv->rps.power;
	switch (dev_priv->rps.power) {
	case LOW_POWER:
		if (val > dev_priv->rps.efficient_freq + 1 && val > dev_priv->rps.cur_freq)
			new_power = BETWEEN;
		break;

	case BETWEEN:
		if (val <= dev_priv->rps.efficient_freq && val < dev_priv->rps.cur_freq)
			new_power = LOW_POWER;
		else if (val >= dev_priv->rps.rp0_freq && val > dev_priv->rps.cur_freq)
			new_power = HIGH_POWER;
		break;

	case HIGH_POWER:
		if (val < (dev_priv->rps.rp1_freq + dev_priv->rps.rp0_freq) >> 1 && val < dev_priv->rps.cur_freq)
			new_power = BETWEEN;
		break;
	}

	if (val <= dev_priv->rps.min_freq_softlimit)
		new_power = LOW_POWER;
	if (val >= dev_priv->rps.max_freq_softlimit)
		new_power = HIGH_POWER;
	if (new_power == dev_priv->rps.power)
		return;


	switch (new_power) {
	case LOW_POWER:

		ei_up = 16000;
		threshold_up = 95;


		ei_down = 32000;
		threshold_down = 85;
		break;

	case BETWEEN:

		ei_up = 13000;
		threshold_up = 90;


		ei_down = 32000;
		threshold_down = 75;
		break;

	case HIGH_POWER:

		ei_up = 10000;
		threshold_up = 85;


		ei_down = 32000;
		threshold_down = 60;
		break;
	}


	if (IS_VALLEYVIEW(dev_priv))
		goto skip_hw_write;

	I915_WRITE(GEN6_RP_UP_EI,
		GT_INTERVAL_FROM_US(dev_priv, ei_up));
	I915_WRITE(GEN6_RP_UP_THRESHOLD,
		GT_INTERVAL_FROM_US(dev_priv, (ei_up * threshold_up / 100)));

	I915_WRITE(GEN6_RP_DOWN_EI,
		GT_INTERVAL_FROM_US(dev_priv, ei_down));
	I915_WRITE(GEN6_RP_DOWN_THRESHOLD,
		GT_INTERVAL_FROM_US(dev_priv, (ei_down * threshold_down / 100)));

	 I915_WRITE(GEN6_RP_CONTROL,
		    GEN6_RP_MEDIA_TURBO |
		    GEN6_RP_MEDIA_HW_NORMAL_MODE |
		    GEN6_RP_MEDIA_IS_GFX |
		    GEN6_RP_ENABLE |
		    GEN6_RP_UP_BUSY_AVG |
		    GEN6_RP_DOWN_IDLE_AVG);

skip_hw_write:
	dev_priv->rps.power = new_power;
	dev_priv->rps.up_threshold = threshold_up;
	dev_priv->rps.down_threshold = threshold_down;
	dev_priv->rps.last_adj = 0;
}
