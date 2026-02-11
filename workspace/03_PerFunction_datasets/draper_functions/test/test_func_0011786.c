save_undo(void)
{
	type8 *tmp, i;
	type32 tmp32;

	tmp = undo[0];
	undo[0] = undo[1];
	undo[1] = tmp;

	for (i = 0; i < 18; i++)
	{
		tmp32 = undo_regs[0][i];
		undo_regs[0][i] = undo_regs[1][i];
		undo_regs[1][i] = tmp32;
	}

	memcpy(undo[1], code, undo_size);
	for (i = 0; i < 8; i++)
	{
		undo_regs[1][i] = dreg[i];
		undo_regs[1][8 + i] = areg[i];
	}
	undo_regs[1][16] = i_count;
	undo_regs[1][17] = pc;

	undo_stat[0] = undo_stat[1];
	undo_stat[1] = 1;
}
