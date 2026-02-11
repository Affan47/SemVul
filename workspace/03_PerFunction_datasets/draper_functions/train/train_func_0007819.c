g4x_aux_data_reg(struct drm_i915_private *dev_priv,
					enum port port, int index)
{
	switch (port) {
	case PORT_B:
	case PORT_C:
	case PORT_D:
		return DP_AUX_CH_DATA(port, index);
	default:
		MISSING_CASE(port);
		return DP_AUX_CH_DATA(PORT_B, index);
	}
}
