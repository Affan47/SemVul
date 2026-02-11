qib_get_pkey(struct qib_ibport *ibp, unsigned index)
{
	struct qib_pportdata *ppd = ppd_from_ibp(ibp);
	struct qib_devdata *dd = ppd->dd;
	unsigned ctxt = ppd->hw_pidx;
	unsigned ret;


	if (!dd->rcd || index >= ARRAY_SIZE(dd->rcd[ctxt]->pkeys))
		ret = 0;
	else
		ret = dd->rcd[ctxt]->pkeys[index];

	return ret;
}
