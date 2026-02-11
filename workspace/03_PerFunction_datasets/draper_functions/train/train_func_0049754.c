gm204_i2c_aux_new(struct nvkm_i2c_pad *pad, int index, u8 drive,
		struct nvkm_i2c_aux **paux)
{
	struct gm204_i2c_aux *aux;

	if (!(aux = kzalloc(sizeof(*aux), GFP_KERNEL)))
		return -ENOMEM;
	*paux = &aux->base;

	nvkm_i2c_aux_ctor(&gm204_i2c_aux_func, pad, index, &aux->base);
	aux->ch = drive;
	aux->base.intr = 1 << aux->ch;
	return 0;
}
