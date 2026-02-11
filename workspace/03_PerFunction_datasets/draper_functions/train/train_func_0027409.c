mxm_shadow(struct nvkm_mxm *mxm, u8 version)
{
	struct mxm_shadow_h *shadow = _mxm_shadow;
	do {
		nvkm_debug(&mxm->subdev, "checking %s\n", shadow->name);
		if (shadow->exec(mxm, version)) {
			if (mxms_valid(mxm))
				return 0;
			kfree(mxm->mxms);
			mxm->mxms = NULL;
		}
	} while ((++shadow)->name);
	return -ENOENT;
}
