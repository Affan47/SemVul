write_7322_creg_port(const struct qib_pportdata *ppd,
					u16 regno, u64 value)
{
	if (ppd->cpspec && ppd->cpspec->cpregbase &&
	    (ppd->dd->flags & QIB_PRESENT))
		writeq(value, &ppd->cpspec->cpregbase[regno]);
}
