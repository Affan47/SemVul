intel_fbc_flush(struct drm_i915_private *dev_priv,
		     unsigned int frontbuffer_bits, enum fb_op_origin origin)
{
	struct intel_fbc *fbc = &dev_priv->fbc;

	if (!fbc_supported(dev_priv))
		return;

	if (origin == ORIGIN_GTT || origin == ORIGIN_FLIP)
		return;

	mutex_lock(&fbc->lock);

	fbc->busy_bits &= ~frontbuffer_bits;

	if (!fbc->busy_bits && fbc->enabled &&
	    (frontbuffer_bits & intel_fbc_get_frontbuffer_bit(fbc))) {
		if (fbc->active)
			intel_fbc_recompress(dev_priv);
		else
			__intel_fbc_post_update(fbc->crtc);
	}

	mutex_unlock(&fbc->lock);
}
