read_pll_ref(struct nv50_clk *clk, u32 base)
{
	struct nvkm_subdev *subdev = &clk->base.subdev;
	struct nvkm_device *device = subdev->device;
	u32 src, mast = nvkm_rd32(device, 0x00c040);

	switch (base) {
	case 0x004028:
		src = !!(mast & 0x00200000);
		break;
	case 0x004020:
		src = !!(mast & 0x00400000);
		break;
	case 0x004008:
		src = !!(mast & 0x00010000);
		break;
	case 0x004030:
		src = !!(mast & 0x02000000);
		break;
	case 0x00e810:
		return nvkm_clk_read(&clk->base, nv_clk_src_crystal);
	default:
		nvkm_error(subdev, "bad pll %06x\n", base);
		return 0;
	}

	if (src)
		return nvkm_clk_read(&clk->base, nv_clk_src_href);

	return read_pll_src(clk, base);
}
