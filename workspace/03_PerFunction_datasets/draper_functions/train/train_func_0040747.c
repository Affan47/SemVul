nvkm_engine_init(struct nvkm_subdev *subdev)
{
	struct nvkm_engine *engine = nvkm_engine(subdev);
	struct nvkm_fb *fb = subdev->device->fb;
	int ret = 0, i;
	s64 time;

	if (!engine->usecount) {
		nvkm_trace(subdev, "init skipped, engine has no users\n");
		return ret;
	}

	if (engine->func->oneinit && !engine->subdev.oneinit) {
		nvkm_trace(subdev, "one-time init running...\n");
		time = ktime_to_us(ktime_get());
		ret = engine->func->oneinit(engine);
		if (ret) {
			nvkm_trace(subdev, "one-time init failed, %d\n", ret);
			return ret;
		}

		engine->subdev.oneinit = true;
		time = ktime_to_us(ktime_get()) - time;
		nvkm_trace(subdev, "one-time init completed in %lldus\n", time);
	}

	if (engine->func->init)
		ret = engine->func->init(engine);

	for (i = 0; fb && i < fb->tile.regions; i++)
		nvkm_engine_tile(engine, i);
	return ret;
}
