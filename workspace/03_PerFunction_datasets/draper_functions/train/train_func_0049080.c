qib_6120_put_tid_2(struct qib_devdata *dd, u64 __iomem *tidptr,
			       u32 type, unsigned long pa)
{
	u32 __iomem *tidp32 = (u32 __iomem *)tidptr;
	u32 tidx;

	if (!dd->kregbase)
		return;

	if (pa != dd->tidinvalid) {
		if (pa & ((1U << 11) - 1)) {
			qib_dev_err(dd, "Physaddr %lx not 2KB aligned!\n",
				    pa);
			return;
		}
		pa >>= 11;
		if (pa & ~QLOGIC_IB_RT_ADDR_MASK) {
			qib_dev_err(dd,
				"Physical page address 0x%lx larger than supported\n",
				pa);
			return;
		}

		if (type == RCVHQ_RCV_TYPE_EAGER)
			pa |= dd->tidtemplate;
		else
			pa |= 2 << 29;
	}
	tidx = tidptr - dd->egrtidbase;
	writel(pa, tidp32);
	mmiowb();
}
