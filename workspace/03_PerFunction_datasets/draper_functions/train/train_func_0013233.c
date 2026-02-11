mmu_op30 (uaecptr pc, uae_u32 opcode, uae_u16 extra, uaecptr extraa)
{
	int type = extra >> 13;

	switch (type)
	{
	case 0:
	case 2:
	case 3:
		mmu_op30_pmove (pc, opcode, extra, extraa);
	break;
	case 1:
		mmu_op30_pflush (pc, opcode, extra, extraa);
	break;
	case 4:
		mmu_op30_ptest (pc, opcode, extra, extraa);
	break;
	default:
		op_illg (opcode);
	break;
	}
}
