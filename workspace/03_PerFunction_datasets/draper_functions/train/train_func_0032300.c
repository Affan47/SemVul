drm_dp_update_payload_part2(struct drm_dp_mst_topology_mgr *mgr)
{
	struct drm_dp_mst_port *port;
	int i;
	int ret = 0;
	mutex_lock(&mgr->payload_lock);
	for (i = 0; i < mgr->max_payloads; i++) {

		if (!mgr->proposed_vcpis[i])
			continue;

		port = container_of(mgr->proposed_vcpis[i], struct drm_dp_mst_port, vcpi);

		DRM_DEBUG_KMS("payload %d %d\n", i, mgr->payloads[i].payload_state);
		if (mgr->payloads[i].payload_state == DP_PAYLOAD_LOCAL) {
			ret = drm_dp_create_payload_step2(mgr, port, mgr->proposed_vcpis[i]->vcpi, &mgr->payloads[i]);
		} else if (mgr->payloads[i].payload_state == DP_PAYLOAD_DELETE_LOCAL) {
			ret = drm_dp_destroy_payload_step2(mgr, mgr->proposed_vcpis[i]->vcpi, &mgr->payloads[i]);
		}
		if (ret) {
			mutex_unlock(&mgr->payload_lock);
			return ret;
		}
	}
	mutex_unlock(&mgr->payload_lock);
	return 0;
}
