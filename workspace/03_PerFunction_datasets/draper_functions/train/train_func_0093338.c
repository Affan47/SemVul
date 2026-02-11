drm_dp_mst_put_payload_id(struct drm_dp_mst_topology_mgr *mgr,
				      int vcpi)
{
	int i;
	if (vcpi == 0)
		return;

	mutex_lock(&mgr->payload_lock);
	DRM_DEBUG_KMS("putting payload %d\n", vcpi);
	clear_bit(vcpi - 1, &mgr->vcpi_mask);

	for (i = 0; i < mgr->max_payloads; i++) {
		if (mgr->proposed_vcpis[i])
			if (mgr->proposed_vcpis[i]->vcpi == vcpi) {
				mgr->proposed_vcpis[i] = NULL;
				clear_bit(i + 1, &mgr->payload_mask);
			}
	}
	mutex_unlock(&mgr->payload_lock);
}
