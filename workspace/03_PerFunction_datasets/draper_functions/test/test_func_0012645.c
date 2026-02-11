main(int argc, char **argv)
{
	int fd;
	int devid;

	if (argc != 1) {
		fprintf(stderr, "usage: %s\n", argv[0]);
		exit(-1);
	}

	fd = drm_open_any();
	devid = intel_get_drm_devid(fd);
	if (!HAS_BLT_RING(devid)) {
		fprintf(stderr, "not (yet) implemented for pre-snb\n");
		return 77;
	}

	bufmgr = drm_intel_bufmgr_gem_init(fd, 4096);
	if (!bufmgr) {
		fprintf(stderr, "failed to init libdrm\n");
		exit(-1);
	}
	drm_intel_bufmgr_gem_enable_reuse(bufmgr);

	batch = intel_batchbuffer_alloc(bufmgr, devid);
	if (!batch) {
		fprintf(stderr, "failed to create batch buffer\n");
		exit(-1);
	}

	target_buffer = drm_intel_bo_alloc(bufmgr, "target bo", 4096, 4096);
	if (!target_buffer) {
		fprintf(stderr, "failed to alloc target buffer\n");
		exit(-1);
	}

	blt_bo = drm_intel_bo_alloc(bufmgr, "target bo", 4*4096*4096, 4096);
	if (!blt_bo) {
		fprintf(stderr, "failed to alloc blt buffer\n");
		exit(-1);
	}

	dummy_reloc_loop();

	drm_intel_bo_unreference(target_buffer);
	intel_batchbuffer_free(batch);
	drm_intel_bufmgr_destroy(bufmgr);

	close(fd);

	return 0;
}
