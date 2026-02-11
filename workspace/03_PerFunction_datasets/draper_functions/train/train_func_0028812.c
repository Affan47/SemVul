ibx_get_dpll(struct intel_crtc *crtc, struct intel_crtc_state *crtc_state,
	     struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	struct intel_shared_dpll *pll;
	enum intel_dpll_id i;

	if (HAS_PCH_IBX(dev_priv)) {

		i = (enum intel_dpll_id) crtc->pipe;
		pll = &dev_priv->shared_dplls[i];

		DRM_DEBUG_KMS("CRTC:%d using pre-allocated %s\n",
			      crtc->base.base.id, pll->name);
	} else {
		pll = intel_find_shared_dpll(crtc, crtc_state,
					     DPLL_ID_PCH_PLL_A,
					     DPLL_ID_PCH_PLL_B);
	}

	if (!pll)
		return NULL;


	intel_reference_shared_dpll(pll, crtc_state);

	return pll;
}
