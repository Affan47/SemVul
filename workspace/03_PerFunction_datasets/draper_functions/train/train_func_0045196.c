nv03_gr_mthd_ttri(struct nvkm_device *device, u32 inst, u32 mthd, u32 data)
{
	bool (*func)(struct nvkm_device *, u32, u32);
	switch (mthd) {
	case 0x0188: func = nv01_gr_mthd_bind_clip; break;
	case 0x018c: func = nv04_gr_mthd_bind_surf_color; break;
	case 0x0190: func = nv04_gr_mthd_bind_surf_zeta; break;
	default:
		return false;
	}
	return func(device, inst, data);
}
