qib_7322_handle_hwerrors(struct qib_devdata *dd, char *msg,
				     size_t msgl)
{
	u64 hwerrs;
	u32 ctrl;
	int isfatal = 0;

	hwerrs = qib_read_kreg64(dd, kr_hwerrstatus);
	if (!hwerrs)
		goto bail;
	if (hwerrs == ~0ULL) {
		qib_dev_err(dd,
			"Read of hardware error status failed (all bits set); ignoring\n");
		goto bail;
	}
	qib_stats.sps_hwerrs++;


	qib_write_kreg(dd, kr_hwerrclear, hwerrs &
		       ~HWE_MASK(PowerOnBISTFailed));

	hwerrs &= dd->cspec->hwerrmask;


	if (hwerrs)
		qib_devinfo(dd->pcidev,
			"Hardware error: hwerr=0x%llx (cleared)\n",
			(unsigned long long) hwerrs);

	ctrl = qib_read_kreg32(dd, kr_control);
	if ((ctrl & SYM_MASK(Control, FreezeMode)) && !dd->diag_client) {


		if ((hwerrs & ~HWE_MASK(LATriggered)) ||
		    dd->cspec->stay_in_freeze) {


			if (dd->flags & QIB_INITTED)
				isfatal = 1;
		} else
			qib_7322_clear_freeze(dd);
	}

	if (hwerrs & HWE_MASK(PowerOnBISTFailed)) {
		isfatal = 1;
		strlcpy(msg,
			"[Memory BIST test failed, InfiniPath hardware unusable]",
			msgl);

		dd->cspec->hwerrmask &= ~HWE_MASK(PowerOnBISTFailed);
		qib_write_kreg(dd, kr_hwerrmask, dd->cspec->hwerrmask);
	}

	err_decode(msg, msgl, hwerrs, qib_7322_hwerror_msgs);


	qib_dev_err(dd, "%s hardware error\n", msg);

	if (hwerrs &
		   (SYM_MASK(HwErrMask, SDmaMemReadErrMask_0) |
		    SYM_MASK(HwErrMask, SDmaMemReadErrMask_1))) {
		int pidx = 0;
		int err;
		unsigned long flags;
		struct qib_pportdata *ppd = dd->pport;

		for (; pidx < dd->num_pports; ++pidx, ppd++) {
			err = 0;
			if (pidx == 0 && (hwerrs &
				SYM_MASK(HwErrMask, SDmaMemReadErrMask_0)))
				err++;
			if (pidx == 1 && (hwerrs &
				SYM_MASK(HwErrMask, SDmaMemReadErrMask_1)))
				err++;
			if (err) {
				spin_lock_irqsave(&ppd->sdma_lock, flags);
				dump_sdma_7322_state(ppd);
				spin_unlock_irqrestore(&ppd->sdma_lock, flags);
			}
		}
	}

	if (isfatal && !dd->diag_client) {
		qib_dev_err(dd,
			"Fatal Hardware Error, no longer usable, SN %.16s\n",
			dd->serial);


		if (dd->freezemsg)
			snprintf(dd->freezemsg, dd->freezelen,
				 "{%s}", msg);
		qib_disable_after_error(dd);
	}
bail:;
}
