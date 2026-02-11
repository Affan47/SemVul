nvkm_devinit_mmio(struct nvkm_devinit *init, u32 addr)
{
	if (init->func->mmio)
		addr = init->func->mmio(init, addr);
	return addr;
}
