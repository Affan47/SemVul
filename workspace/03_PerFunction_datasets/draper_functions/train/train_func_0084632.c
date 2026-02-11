init_exec_set(struct nvbios_init *init, bool exec)
{
	if (exec) init->execute &= 0xfd;
	else      init->execute |= 0x02;
}
