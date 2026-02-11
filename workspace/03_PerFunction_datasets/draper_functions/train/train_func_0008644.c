nvkm_output_dp_ctor(const struct nvkm_output_dp_func *func,
		    struct nvkm_disp *disp, int index, struct dcb_output *dcbE,
		    struct nvkm_i2c_aux *aux, struct nvkm_output_dp *outp)
{
	struct nvkm_device *device = disp->engine.subdev.device;
	struct nvkm_bios *bios = device->bios;
	struct nvkm_i2c *i2c = device->i2c;
	u8  hdr, cnt, len;
	u32 data;
	int ret;

	nvkm_output_ctor(&nvkm_output_dp_func, disp, index, dcbE, &outp->base);
	outp->func = func;
	outp->aux = aux;
	if (!outp->aux) {
		OUTP_ERR(&outp->base, "no aux");
		return -ENODEV;
	}


	data = nvbios_dpout_match(bios, outp->base.info.hasht,
				  outp->base.info.hashm, &outp->version,
				  &hdr, &cnt, &len, &outp->info);
	if (!data) {
		OUTP_ERR(&outp->base, "no bios dp data");
		return -ENODEV;
	}

	OUTP_DBG(&outp->base, "bios dp %02x %02x %02x %02x",
		 outp->version, hdr, cnt, len);


	INIT_WORK(&outp->lt.work, nvkm_dp_train);
	init_waitqueue_head(&outp->lt.wait);
	atomic_set(&outp->lt.done, 0);


	ret = nvkm_notify_init(NULL, &i2c->event, nvkm_output_dp_irq, true,
			       &(struct nvkm_i2c_ntfy_req) {
				.mask = NVKM_I2C_IRQ,
				.port = outp->aux->id,
			       },
			       sizeof(struct nvkm_i2c_ntfy_req),
			       sizeof(struct nvkm_i2c_ntfy_rep),
			       &outp->irq);
	if (ret) {
		OUTP_ERR(&outp->base, "error monitoring aux irq: %d", ret);
		return ret;
	}


	ret = nvkm_notify_init(NULL, &i2c->event, nvkm_output_dp_hpd, true,
			       &(struct nvkm_i2c_ntfy_req) {
				.mask = NVKM_I2C_PLUG | NVKM_I2C_UNPLUG,
				.port = outp->aux->id,
			       },
			       sizeof(struct nvkm_i2c_ntfy_req),
			       sizeof(struct nvkm_i2c_ntfy_rep),
			       &outp->hpd);
	if (ret) {
		OUTP_ERR(&outp->base, "error monitoring aux hpd: %d", ret);
		return ret;
	}

	return 0;
}
