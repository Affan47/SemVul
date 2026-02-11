__intel_fbc_cleanup_cfb(struct drm_i915_private *dev_priv)
{
	if (dev_priv->fbc.uncompressed_size == 0)
		return;

	i915_gem_stolen_remove_node(dev_priv, &dev_priv->fbc.compressed_fb);

	if (dev_priv->fbc.compressed_llb) {
		i915_gem_stolen_remove_node(dev_priv,
					    dev_priv->fbc.compressed_llb);
		kfree(dev_priv->fbc.compressed_llb);
	}

	dev_priv->fbc.uncompressed_size = 0;
}
