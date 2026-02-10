nv01_gr_mthd_bind_clip(struct nvkm_device *device, u32 inst, u32 data)
{
	switch (nv04_gr_mthd_bind_class(device, data)) {
	case 0x30:
		nv04_gr_set_ctx1(device, inst, 0x2000, 0);
		return true;
	case 0x19:
		nv04_gr_set_ctx1(device, inst, 0x2000, 0x2000);
		return true;
	}
	return false;
}
