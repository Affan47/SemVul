init_compute_mem(struct nvbios_init *init)
{
	struct nvkm_devinit *devinit = init->bios->subdev.device->devinit;

	trace("COMPUTE_MEM\n");
	init->offset += 1;

	init_exec_force(init, true);
	if (init_exec(init))
		nvkm_devinit_meminit(devinit);
	init_exec_force(init, false);
}
