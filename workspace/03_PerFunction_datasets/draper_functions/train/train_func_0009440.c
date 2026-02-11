filesys_init_storeinfo (TrapContext *context)
{
	int ret = -1;
	switch (m68k_dreg (regs, 1))
	{
	case 1:
		mountertask = m68k_areg (regs, 1);
#ifdef PICASSO96
		picasso96_alloc (context);
#endif
		break;
	case 2:
		ret = automountunit;
		automountunit = -1;
		break;
	case 3:
		return 0;
	}
	return ret;
}
