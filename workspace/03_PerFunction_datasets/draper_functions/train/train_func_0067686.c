nv04_gr_mthd_surf3d(struct nvkm_device *device, u32 inst, u32 mthd, u32 data)
{
	bool (*func)(struct nvkm_device *, u32, u32);
	switch (mthd) {
	case 0x02f8: func = nv04_gr_mthd_surf3d_clip_h; break;
	case 0x02fc: func = nv04_gr_mthd_surf3d_clip_v; break;
	default:
		return false;
	}
	return func(device, inst, data);
}
