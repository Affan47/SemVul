gf119_disp_intr_error(struct nv50_disp *disp, int chid)
{
	struct nvkm_subdev *subdev = &disp->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 mthd = nvkm_rd32(device, 0x6101f0 + (chid * 12));
	u32 data = nvkm_rd32(device, 0x6101f4 + (chid * 12));
	u32 unkn = nvkm_rd32(device, 0x6101f8 + (chid * 12));

	nvkm_error(subdev, "chid %d mthd %04x data %08x %08x %08x\n",
		   chid, (mthd & 0x0000ffc), data, mthd, unkn);

	if (chid < ARRAY_SIZE(disp->chan)) {
		switch (mthd & 0xffc) {
		case 0x0080:
			nv50_disp_chan_mthd(disp->chan[chid], NV_DBG_ERROR);
			break;
		default:
			break;
		}
	}

	nvkm_wr32(device, 0x61009c, (1 << chid));
	nvkm_wr32(device, 0x6101f0 + (chid * 12), 0x90000000);
}
