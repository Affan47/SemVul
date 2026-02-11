anx9805_aux_lnk_ctl(struct nvkm_i2c_aux *base,
		    int link_nr, int link_bw, bool enh)
{
	struct anx9805_aux *aux = anx9805_aux(base);
	struct anx9805_pad *pad = aux->pad;
	struct i2c_adapter *adap = &pad->bus->i2c;
	u8 tmp, i;

	AUX_DBG(&aux->base, "ANX9805 train %d %02x %d",
		link_nr, link_bw, enh);

	nvkm_wri2cr(adap, aux->addr, 0xa0, link_bw);
	nvkm_wri2cr(adap, aux->addr, 0xa1, link_nr | (enh ? 0x80 : 0x00));
	nvkm_wri2cr(adap, aux->addr, 0xa2, 0x01);
	nvkm_wri2cr(adap, aux->addr, 0xa8, 0x01);

	i = 0;
	while ((tmp = nvkm_rdi2cr(adap, aux->addr, 0xa8)) & 0x01) {
		mdelay(5);
		if (i++ == 100) {
			AUX_ERR(&aux->base, "link training timeout");
			return -ETIMEDOUT;
		}
	}

	if (tmp & 0x70) {
		AUX_ERR(&aux->base, "link training failed");
		return -EIO;
	}

	return 0;
}
