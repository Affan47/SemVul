ironlake_enable_drps(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 rgvmodectl = I915_READ(MEMMODECTL);
	u8 fmax, fmin, fstart, vstart;

	spin_lock_irq(&mchdev_lock);


	I915_WRITE16(PMMISC, I915_READ(PMMISC) | MCPPCE_EN);
	I915_WRITE16(TSC1, I915_READ(TSC1) | TSE);


	I915_WRITE(RCUPEI, 100000);
	I915_WRITE(RCDNEI, 100000);


	I915_WRITE(RCBMAXAVG, 90000);
	I915_WRITE(RCBMINAVG, 80000);

	I915_WRITE(MEMIHYST, 1);


	fmax = (rgvmodectl & MEMMODE_FMAX_MASK) >> MEMMODE_FMAX_SHIFT;
	fmin = (rgvmodectl & MEMMODE_FMIN_MASK);
	fstart = (rgvmodectl & MEMMODE_FSTART_MASK) >>
		MEMMODE_FSTART_SHIFT;

	vstart = (I915_READ(PXVFREQ(fstart)) & PXVFREQ_PX_MASK) >>
		PXVFREQ_PX_SHIFT;

	dev_priv->ips.fmax = fmax;
	dev_priv->ips.fstart = fstart;

	dev_priv->ips.max_delay = fstart;
	dev_priv->ips.min_delay = fmin;
	dev_priv->ips.cur_delay = fstart;

	DRM_DEBUG_DRIVER("fmax: %d, fmin: %d, fstart: %d\n",
			 fmax, fmin, fstart);

	I915_WRITE(MEMINTREN, MEMINT_CX_SUPR_EN | MEMINT_EVAL_CHG_EN);


	I915_WRITE(VIDSTART, vstart);
	POSTING_READ(VIDSTART);

	rgvmodectl |= MEMMODE_SWMODE_EN;
	I915_WRITE(MEMMODECTL, rgvmodectl);

	if (wait_for_atomic((I915_READ(MEMSWCTL) & MEMCTL_CMD_STS) == 0, 10))
		DRM_ERROR("stuck trying to change perf mode\n");
	mdelay(1);

	ironlake_set_drps(dev, fstart);

	dev_priv->ips.last_count1 = I915_READ(DMIEC) +
		I915_READ(DDREC) + I915_READ(CSIEC);
	dev_priv->ips.last_time1 = jiffies_to_msecs(jiffies);
	dev_priv->ips.last_count2 = I915_READ(GFXEC);
	dev_priv->ips.last_time2 = ktime_get_raw_ns();

	spin_unlock_irq(&mchdev_lock);
}
