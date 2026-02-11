nvkm_i2c_pad_del(struct nvkm_i2c_pad **ppad)
{
	struct nvkm_i2c_pad *pad = *ppad;
	if (pad) {
		PAD_TRACE(pad, "dtor");
		list_del(&pad->head);
		kfree(pad);
		pad = NULL;
	}
}
