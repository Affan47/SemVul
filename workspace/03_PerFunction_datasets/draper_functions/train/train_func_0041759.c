qib_disable_after_error(struct qib_devdata *dd)
{
	if (dd->flags & QIB_INITTED) {
		u32 pidx;

		dd->flags &= ~QIB_INITTED;
		if (dd->pport)
			for (pidx = 0; pidx < dd->num_pports; ++pidx) {
				struct qib_pportdata *ppd;

				ppd = dd->pport + pidx;
				if (dd->flags & QIB_PRESENT) {
					qib_set_linkstate(ppd,
						QIB_IB_LINKDOWN_DISABLE);
					dd->f_setextled(ppd, 0);
				}
				*ppd->statusp &= ~QIB_STATUS_IB_READY;
			}
	}


	if (dd->devstatusp)
		*dd->devstatusp |= QIB_STATUS_HWERROR;
}
