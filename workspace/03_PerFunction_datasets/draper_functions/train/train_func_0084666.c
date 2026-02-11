init_prog_pll(struct nvbios_init *init, u32 id, u32 freq)
{
	struct nvkm_devinit *devinit = init->bios->subdev.device->devinit;
	if (init_exec(init)) {
		int ret = nvkm_devinit_pll_set(devinit, id, freq);
		if (ret)
			warn("failed to prog pll 0x%08x to %dkHz\n", id, freq);
	}
}
