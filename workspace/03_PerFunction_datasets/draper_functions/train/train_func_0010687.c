make_rpcs(struct drm_device *dev)
{
	u32 rpcs = 0;


	if (INTEL_INFO(dev)->gen < 9)
		return 0;


	if (INTEL_INFO(dev)->has_slice_pg) {
		rpcs |= GEN8_RPCS_S_CNT_ENABLE;
		rpcs |= INTEL_INFO(dev)->slice_total <<
			GEN8_RPCS_S_CNT_SHIFT;
		rpcs |= GEN8_RPCS_ENABLE;
	}

	if (INTEL_INFO(dev)->has_subslice_pg) {
		rpcs |= GEN8_RPCS_SS_CNT_ENABLE;
		rpcs |= INTEL_INFO(dev)->subslice_per_slice <<
			GEN8_RPCS_SS_CNT_SHIFT;
		rpcs |= GEN8_RPCS_ENABLE;
	}

	if (INTEL_INFO(dev)->has_eu_pg) {
		rpcs |= INTEL_INFO(dev)->eu_per_subslice <<
			GEN8_RPCS_EU_MIN_SHIFT;
		rpcs |= INTEL_INFO(dev)->eu_per_subslice <<
			GEN8_RPCS_EU_MAX_SHIFT;
		rpcs |= GEN8_RPCS_ENABLE;
	}

	return rpcs;
}
