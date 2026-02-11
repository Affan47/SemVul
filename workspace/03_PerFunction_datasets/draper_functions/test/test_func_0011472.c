intel_suspend_hw(struct drm_device *dev)
{
	if (HAS_PCH_LPT(dev))
		lpt_suspend_hw(dev);
}
