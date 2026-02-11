nouveau_connector_hotplug(struct nvif_notify *notify)
{
	struct nouveau_connector *nv_connector =
		container_of(notify, typeof(*nv_connector), hpd);
	struct drm_connector *connector = &nv_connector->base;
	struct nouveau_drm *drm = nouveau_drm(connector->dev);
	const struct nvif_notify_conn_rep_v0 *rep = notify->data;
	const char *name = connector->name;

	if (rep->mask & NVIF_NOTIFY_CONN_V0_IRQ) {
	} else {
		bool plugged = (rep->mask != NVIF_NOTIFY_CONN_V0_UNPLUG);

		NV_DEBUG(drm, "%splugged %s\n", plugged ? "" : "un", name);

		mutex_lock(&drm->dev->mode_config.mutex);
		if (plugged)
			drm_helper_connector_dpms(connector, DRM_MODE_DPMS_ON);
		else
			drm_helper_connector_dpms(connector, DRM_MODE_DPMS_OFF);
		mutex_unlock(&drm->dev->mode_config.mutex);

		drm_helper_hpd_irq_event(connector->dev);
	}

	return NVIF_NOTIFY_KEEP;
}
