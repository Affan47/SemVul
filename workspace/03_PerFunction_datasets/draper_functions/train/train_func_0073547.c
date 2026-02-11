qib_chk_6120_errormask(struct qib_devdata *dd)
{
	static u32 fixed;
	u32 ctrl;
	unsigned long errormask;
	unsigned long hwerrs;

	if (!dd->cspec->errormask || !(dd->flags & QIB_INITTED))
		return;

	errormask = qib_read_kreg64(dd, kr_errmask);

	if (errormask == dd->cspec->errormask)
		return;
	fixed++;

	hwerrs = qib_read_kreg64(dd, kr_hwerrstatus);
	ctrl = qib_read_kreg32(dd, kr_control);

	qib_write_kreg(dd, kr_errmask,
		dd->cspec->errormask);

	if ((hwerrs & dd->cspec->hwerrmask) ||
	    (ctrl & QLOGIC_IB_C_FREEZEMODE)) {
		qib_write_kreg(dd, kr_hwerrclear, 0ULL);
		qib_write_kreg(dd, kr_errclear, 0ULL);

		qib_write_kreg(dd, kr_intclear, 0ULL);
		qib_devinfo(dd->pcidev,
			 "errormask fixed(%u) %lx->%lx, ctrl %x hwerr %lx\n",
			 fixed, errormask, (unsigned long)dd->cspec->errormask,
			 ctrl, hwerrs);
	}
}
