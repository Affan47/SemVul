nv50_display_init(struct drm_device *dev)
{
	struct nv50_disp *disp = nv50_disp(dev);
	struct drm_crtc *crtc;
	u32 *push;

	push = evo_wait(nv50_mast(dev), 32);
	if (!push)
		return -EBUSY;

	list_for_each_entry(crtc, &dev->mode_config.crtc_list, head) {
		struct nv50_sync *sync = nv50_sync(crtc);

		nv50_crtc_lut_load(crtc);
		nouveau_bo_wr32(disp->sync, sync->addr / 4, sync->data);
	}

	evo_mthd(push, 0x0088, 1);
	evo_data(push, nv50_mast(dev)->base.sync.handle);
	evo_kick(push, nv50_mast(dev));
	return 0;
}
