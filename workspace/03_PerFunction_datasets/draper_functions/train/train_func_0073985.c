get_7220_chip_params(struct qib_devdata *dd)
{
	u64 val;
	u32 piobufs;
	int mtu;

	dd->uregbase = qib_read_kreg32(dd, kr_userregbase);

	dd->rcvtidcnt = qib_read_kreg32(dd, kr_rcvtidcnt);
	dd->rcvtidbase = qib_read_kreg32(dd, kr_rcvtidbase);
	dd->rcvegrbase = qib_read_kreg32(dd, kr_rcvegrbase);
	dd->palign = qib_read_kreg32(dd, kr_palign);
	dd->piobufbase = qib_read_kreg64(dd, kr_sendpiobufbase);
	dd->pio2k_bufbase = dd->piobufbase & 0xffffffff;

	val = qib_read_kreg64(dd, kr_sendpiosize);
	dd->piosize2k = val & ~0U;
	dd->piosize4k = val >> 32;

	mtu = ib_mtu_enum_to_int(qib_ibmtu);
	if (mtu == -1)
		mtu = QIB_DEFAULT_MTU;
	dd->pport->ibmtu = (u32)mtu;

	val = qib_read_kreg64(dd, kr_sendpiobufcnt);
	dd->piobcnt2k = val & ~0U;
	dd->piobcnt4k = val >> 32;

	dd->pio2kbase = (u32 __iomem *)
		((char __iomem *) dd->kregbase + dd->pio2k_bufbase);
	if (dd->piobcnt4k) {
		dd->pio4kbase = (u32 __iomem *)
			((char __iomem *) dd->kregbase +
			 (dd->piobufbase >> 32));


		dd->align4k = ALIGN(dd->piosize4k, dd->palign);
	}

	piobufs = dd->piobcnt4k + dd->piobcnt2k;

	dd->pioavregs = ALIGN(piobufs, sizeof(u64) * BITS_PER_BYTE / 2) /
		(sizeof(u64) * BITS_PER_BYTE / 2);
}
