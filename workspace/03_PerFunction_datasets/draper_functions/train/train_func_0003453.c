nv50_sor_dpms(struct drm_encoder *encoder, int mode)
{
	struct nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	struct nv50_disp *disp = nv50_disp(encoder->dev);
	struct {
		struct nv50_disp_mthd_v1 base;
		struct nv50_disp_sor_pwr_v0 pwr;
	} args = {
		.base.version = 1,
		.base.method = NV50_DISP_MTHD_V1_SOR_PWR,
		.base.hasht  = nv_encoder->dcb->hasht,
		.base.hashm  = nv_encoder->dcb->hashm,
		.pwr.state = mode == DRM_MODE_DPMS_ON,
	};
	struct {
		struct nv50_disp_mthd_v1 base;
		struct nv50_disp_sor_dp_pwr_v0 pwr;
	} link = {
		.base.version = 1,
		.base.method = NV50_DISP_MTHD_V1_SOR_DP_PWR,
		.base.hasht  = nv_encoder->dcb->hasht,
		.base.hashm  = nv_encoder->dcb->hashm,
		.pwr.state = mode == DRM_MODE_DPMS_ON,
	};
	struct drm_device *dev = encoder->dev;
	struct drm_encoder *partner;

	nv_encoder->last_dpms = mode;

	list_for_each_entry(partner, &dev->mode_config.encoder_list, head) {
		struct nouveau_encoder *nv_partner = nouveau_encoder(partner);

		if (partner->encoder_type != DRM_MODE_ENCODER_TMDS)
			continue;

		if (nv_partner != nv_encoder &&
		    nv_partner->dcb->or == nv_encoder->dcb->or) {
			if (nv_partner->last_dpms == DRM_MODE_DPMS_ON)
				return;
			break;
		}
	}

	if (nv_encoder->dcb->type == DCB_OUTPUT_DP) {
		args.pwr.state = 1;
		nvif_mthd(disp->disp, 0, &args, sizeof(args));
		nvif_mthd(disp->disp, 0, &link, sizeof(link));
	} else {
		nvif_mthd(disp->disp, 0, &args, sizeof(args));
	}
}
