intel_bios_is_lspcon_present(struct drm_i915_private *dev_priv,
				enum port port)
{
	int i;

	if (!HAS_LSPCON(dev_priv))
		return false;

	for (i = 0; i < dev_priv->vbt.child_dev_num; i++) {
		if (!dev_priv->vbt.child_dev[i].common.lspcon)
			continue;

		switch (dev_priv->vbt.child_dev[i].common.dvo_port) {
		case DVO_PORT_DPA:
		case DVO_PORT_HDMIA:
			if (port == PORT_A)
				return true;
			break;
		case DVO_PORT_DPB:
		case DVO_PORT_HDMIB:
			if (port == PORT_B)
				return true;
			break;
		case DVO_PORT_DPC:
		case DVO_PORT_HDMIC:
			if (port == PORT_C)
				return true;
			break;
		case DVO_PORT_DPD:
		case DVO_PORT_HDMID:
			if (port == PORT_D)
				return true;
			break;
		default:
			break;
		}
	}

	return false;
}
