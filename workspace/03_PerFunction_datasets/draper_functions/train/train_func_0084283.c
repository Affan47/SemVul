nv10_gr_init(struct nvkm_gr *base)
{
	struct nv10_gr *gr = nv10_gr(base);
	struct nvkm_device *device = gr->base.engine.subdev.device;

	nvkm_wr32(device, NV03_PGRAPH_INTR   , 0xFFFFFFFF);
	nvkm_wr32(device, NV03_PGRAPH_INTR_EN, 0xFFFFFFFF);

	nvkm_wr32(device, NV04_PGRAPH_DEBUG_0, 0xFFFFFFFF);
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_0, 0x00000000);
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_1, 0x00118700);

	nvkm_wr32(device, NV04_PGRAPH_DEBUG_2, 0x25f92ad9);
	nvkm_wr32(device, NV04_PGRAPH_DEBUG_3, 0x55DE0830 | (1 << 29) | (1 << 31));

	if (device->card_type >= NV_11 && device->chipset >= 0x17) {
		nvkm_wr32(device, NV10_PGRAPH_DEBUG_4, 0x1f000000);
		nvkm_wr32(device, 0x400a10, 0x03ff3fb6);
		nvkm_wr32(device, 0x400838, 0x002f8684);
		nvkm_wr32(device, 0x40083c, 0x00115f3f);
		nvkm_wr32(device, 0x4006b0, 0x40000020);
	} else {
		nvkm_wr32(device, NV10_PGRAPH_DEBUG_4, 0x00000000);
	}

	nvkm_wr32(device, NV10_PGRAPH_CTX_SWITCH(0), 0x00000000);
	nvkm_wr32(device, NV10_PGRAPH_CTX_SWITCH(1), 0x00000000);
	nvkm_wr32(device, NV10_PGRAPH_CTX_SWITCH(2), 0x00000000);
	nvkm_wr32(device, NV10_PGRAPH_CTX_SWITCH(3), 0x00000000);
	nvkm_wr32(device, NV10_PGRAPH_CTX_SWITCH(4), 0x00000000);
	nvkm_wr32(device, NV10_PGRAPH_STATE, 0xFFFFFFFF);

	nvkm_mask(device, NV10_PGRAPH_CTX_USER, 0xff000000, 0x1f000000);
	nvkm_wr32(device, NV10_PGRAPH_CTX_CONTROL, 0x10000100);
	nvkm_wr32(device, NV10_PGRAPH_FFINTFC_ST2, 0x08000000);
	return 0;
}
