calc_pll(struct gk104_clk *clk, int idx, u32 freq, u32 *coef)
{
	struct nvkm_subdev *subdev = &clk->base.subdev;
	struct nvkm_bios *bios = subdev->device->bios;
	struct nvbios_pll limits;
	int N, M, P, ret;

	ret = nvbios_pll_parse(bios, 0x137000 + (idx * 0x20), &limits);
	if (ret)
		return 0;

	limits.refclk = read_div(clk, idx, 0x137120, 0x137140);
	if (!limits.refclk)
		return 0;

	ret = gt215_pll_calc(subdev, &limits, freq, &N, NULL, &M, &P);
	if (ret <= 0)
		return 0;

	*coef = (P << 16) | (N << 8) | M;
	return ret;
}
