do_step()
{
	int size;
	int size_mem_imm, size_x_imm;

	do_go();

	size_mem_imm = 2;
	if(engine.psr & 0x20) {
		size_mem_imm = 1;
	}
	size_x_imm = 2;
	if(engine.psr & 0x10) {
		size_x_imm = 1;
	}
	size = do_dis(stdout, engine.kpc, size_mem_imm, size_x_imm, 0, 0);
}
