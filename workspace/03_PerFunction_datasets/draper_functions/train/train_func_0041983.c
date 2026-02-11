sendctrl_7220_mod(struct qib_pportdata *ppd, u32 op)
{
	struct qib_devdata *dd = ppd->dd;
	u64 tmp_dd_sendctrl;
	unsigned long flags;

	spin_lock_irqsave(&dd->sendctrl_lock, flags);


	if (op & QIB_SENDCTRL_CLEAR)
		dd->sendctrl = 0;
	if (op & QIB_SENDCTRL_SEND_DIS)
		dd->sendctrl &= ~SYM_MASK(SendCtrl, SPioEnable);
	else if (op & QIB_SENDCTRL_SEND_ENB) {
		dd->sendctrl |= SYM_MASK(SendCtrl, SPioEnable);
		if (dd->flags & QIB_USE_SPCL_TRIG)
			dd->sendctrl |= SYM_MASK(SendCtrl,
						 SSpecialTriggerEn);
	}
	if (op & QIB_SENDCTRL_AVAIL_DIS)
		dd->sendctrl &= ~SYM_MASK(SendCtrl, SendBufAvailUpd);
	else if (op & QIB_SENDCTRL_AVAIL_ENB)
		dd->sendctrl |= SYM_MASK(SendCtrl, SendBufAvailUpd);

	if (op & QIB_SENDCTRL_DISARM_ALL) {
		u32 i, last;

		tmp_dd_sendctrl = dd->sendctrl;


		last = dd->piobcnt2k + dd->piobcnt4k;
		tmp_dd_sendctrl &=
			~(SYM_MASK(SendCtrl, SPioEnable) |
			  SYM_MASK(SendCtrl, SendBufAvailUpd));
		for (i = 0; i < last; i++) {
			qib_write_kreg(dd, kr_sendctrl,
				       tmp_dd_sendctrl |
				       SYM_MASK(SendCtrl, Disarm) | i);
			qib_write_kreg(dd, kr_scratch, 0);
		}
	}

	tmp_dd_sendctrl = dd->sendctrl;

	if (op & QIB_SENDCTRL_FLUSH)
		tmp_dd_sendctrl |= SYM_MASK(SendCtrl, Abort);
	if (op & QIB_SENDCTRL_DISARM)
		tmp_dd_sendctrl |= SYM_MASK(SendCtrl, Disarm) |
			((op & QIB_7220_SendCtrl_DisarmPIOBuf_RMASK) <<
			 SYM_LSB(SendCtrl, DisarmPIOBuf));
	if ((op & QIB_SENDCTRL_AVAIL_BLIP) &&
	    (dd->sendctrl & SYM_MASK(SendCtrl, SendBufAvailUpd)))
		tmp_dd_sendctrl &= ~SYM_MASK(SendCtrl, SendBufAvailUpd);

	qib_write_kreg(dd, kr_sendctrl, tmp_dd_sendctrl);
	qib_write_kreg(dd, kr_scratch, 0);

	if (op & QIB_SENDCTRL_AVAIL_BLIP) {
		qib_write_kreg(dd, kr_sendctrl, dd->sendctrl);
		qib_write_kreg(dd, kr_scratch, 0);
	}

	spin_unlock_irqrestore(&dd->sendctrl_lock, flags);

	if (op & QIB_SENDCTRL_FLUSH) {
		u32 v;


		v = qib_read_kreg32(dd, kr_scratch);
		qib_write_kreg(dd, kr_scratch, v);
		v = qib_read_kreg32(dd, kr_scratch);
		qib_write_kreg(dd, kr_scratch, v);
		qib_read_kreg32(dd, kr_scratch);
	}
}
