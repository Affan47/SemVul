intel_dp_probe_mst(struct intel_dp *intel_dp)
{
	u8 buf[1];

	if (!i915.enable_dp_mst)
		return false;

	if (!intel_dp->can_mst)
		return false;

	if (intel_dp->dpcd[DP_DPCD_REV] < 0x12)
		return false;

	if (drm_dp_dpcd_read(&intel_dp->aux, DP_MSTM_CAP, buf, 1)) {
		if (buf[0] & DP_MST_CAP) {
			DRM_DEBUG_KMS("Sink is MST capable\n");
			intel_dp->is_mst = true;
		} else {
			DRM_DEBUG_KMS("Sink is not MST capable\n");
			intel_dp->is_mst = false;
		}
	}

	drm_dp_mst_topology_mgr_set_mst(&intel_dp->mst_mgr, intel_dp->is_mst);
	return intel_dp->is_mst;
}
