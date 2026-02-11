init_link(struct nvbios_init *init)
{
	if (init_exec(init)) {
		if (init->outp)
			return !(init->outp->sorconf.link & 1);
		error("script needs OR link\n");
	}
	return 0;
}
