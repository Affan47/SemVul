qib_set_7322_armlaunch(struct qib_devdata *dd, u32 enable)
{
	if (enable) {
		qib_write_kreg(dd, kr_errclear, QIB_E_SPIOARMLAUNCH);
		dd->cspec->errormask |= QIB_E_SPIOARMLAUNCH;
	} else
		dd->cspec->errormask &= ~QIB_E_SPIOARMLAUNCH;
	qib_write_kreg(dd, kr_errmask, dd->cspec->errormask);
}
