skl_ddi_pll_enable(struct drm_i915_private *dev_priv,
			       struct intel_shared_dpll *pll)
{
	uint32_t val;
	unsigned int dpll;
	const struct skl_dpll_regs *regs = skl_dpll_regs;


	dpll = pll->id + 1;

	val = I915_READ(DPLL_CTRL1);

	val &= ~(DPLL_CTRL1_HDMI_MODE(dpll) | DPLL_CTRL1_SSC(dpll) |
		 DPLL_CTRL1_LINK_RATE_MASK(dpll));
	val |= pll->config.hw_state.ctrl1 << (dpll * 6);

	I915_WRITE(DPLL_CTRL1, val);
	POSTING_READ(DPLL_CTRL1);

	I915_WRITE(regs[pll->id].cfgcr1, pll->config.hw_state.cfgcr1);
	I915_WRITE(regs[pll->id].cfgcr2, pll->config.hw_state.cfgcr2);
	POSTING_READ(regs[pll->id].cfgcr1);
	POSTING_READ(regs[pll->id].cfgcr2);


	I915_WRITE(regs[pll->id].ctl,
		   I915_READ(regs[pll->id].ctl) | LCPLL_PLL_ENABLE);

	if (wait_for(I915_READ(DPLL_STATUS) & DPLL_LOCK(dpll), 5))
		DRM_ERROR("DPLL %d not locked\n", dpll);
}
