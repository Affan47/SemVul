drm_dp_get_last_connected_port_and_mstb(struct drm_dp_mst_topology_mgr *mgr,
									 struct drm_dp_mst_branch *mstb,
									 int *port_num)
{
	struct drm_dp_mst_branch *rmstb = NULL;
	struct drm_dp_mst_port *found_port;
	mutex_lock(&mgr->lock);
	if (mgr->mst_primary) {
		found_port = drm_dp_get_last_connected_port_to_mstb(mstb);

		if (found_port) {
			rmstb = found_port->parent;
			kref_get(&rmstb->kref);
			*port_num = found_port->port_num;
		}
	}
	mutex_unlock(&mgr->lock);
	return rmstb;
}
