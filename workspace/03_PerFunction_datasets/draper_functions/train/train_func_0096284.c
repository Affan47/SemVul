nvkm_fb_tile_prog(struct nvkm_fb *fb, int region, struct nvkm_fb_tile *tile)
{
	struct nvkm_device *device = fb->subdev.device;
	if (fb->func->tile.prog) {
		fb->func->tile.prog(fb, region, tile);
		if (device->gr)
			nvkm_engine_tile(&device->gr->engine, region);
		if (device->mpeg)
			nvkm_engine_tile(device->mpeg, region);
	}
}
