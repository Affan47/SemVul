init_resume(struct nvbios_init *init)
{
	trace("RESUME\n");
	init->offset += 1;
	init_exec_set(init, true);
}
