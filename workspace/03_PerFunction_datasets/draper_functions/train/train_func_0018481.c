intel_digital_port_connected(struct drm_i915_private *dev_priv,
					 struct intel_digital_port *port)
{
	if (HAS_PCH_IBX(dev_priv))
		return ibx_digital_port_connected(dev_priv, port);
	if (HAS_PCH_SPLIT(dev_priv))
		return cpt_digital_port_connected(dev_priv, port);
	else if (IS_BROXTON(dev_priv))
		return bxt_digital_port_connected(dev_priv, port);
	else if (IS_GM45(dev_priv))
		return gm45_digital_port_connected(dev_priv, port);
	else
		return g4x_digital_port_connected(dev_priv, port);
}
