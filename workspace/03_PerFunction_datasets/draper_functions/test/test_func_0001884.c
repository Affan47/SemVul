is_latch(struct fpga_device *dev)
{
	int i;


	for (i = LUT_A; i <= LUT_D; i++) {
		if (dev->u.logic.a2d[i].ff == FF_LATCH
		    || dev->u.logic.a2d[i].ff == FF_OR2L
		    || dev->u.logic.a2d[i].ff == FF_AND2L)
			return 1;
	}
	return 0;
}
