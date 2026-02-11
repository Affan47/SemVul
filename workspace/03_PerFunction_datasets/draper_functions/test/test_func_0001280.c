isirq (void)
{
	if (superdmac) {
		if ((dmac_cntr & SCNTR_INTEN) && (dmac_istr & (ISTR_INTS | ISTR_E_INT)))
			return 1;
	} else {
		if ((dmac_cntr & CNTR_INTEN) && (dmac_istr & (ISTR_INTS | ISTR_E_INT)))
			return 1;
	}
	return 0;
}
