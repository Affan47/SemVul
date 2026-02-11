flush_fifo(struct qib_pportdata *ppd)
{
	struct qib_devdata *dd = ppd->dd;
	u32 __iomem *piobuf;
	u32 bufn;
	u32 *hdr;
	u64 pbc;
	const unsigned hdrwords = 7;
	static struct qib_ib_header ibhdr = {
		.lrh[0] = cpu_to_be16(0xF000 | QIB_LRH_BTH),
		.lrh[1] = IB_LID_PERMISSIVE,
		.lrh[2] = cpu_to_be16(hdrwords + SIZE_OF_CRC),
		.lrh[3] = IB_LID_PERMISSIVE,
		.u.oth.bth[0] = cpu_to_be32(
			(IB_OPCODE_UD_SEND_ONLY << 24) | QIB_DEFAULT_P_KEY),
		.u.oth.bth[1] = cpu_to_be32(0),
		.u.oth.bth[2] = cpu_to_be32(0),
		.u.oth.u.ud.deth[0] = cpu_to_be32(0),
		.u.oth.u.ud.deth[1] = cpu_to_be32(0),
	};


	pbc = PBC_7322_VL15_SEND |
		(((u64)ppd->hw_pidx) << (PBC_PORT_SEL_LSB + 32)) |
		(hdrwords + SIZE_OF_CRC);
	piobuf = qib_7322_getsendbuf(ppd, pbc, &bufn);
	if (!piobuf)
		return;
	writeq(pbc, piobuf);
	hdr = (u32 *) &ibhdr;
	if (dd->flags & QIB_PIO_FLUSH_WC) {
		qib_flush_wc();
		qib_pio_copy(piobuf + 2, hdr, hdrwords - 1);
		qib_flush_wc();
		__raw_writel(hdr[hdrwords - 1], piobuf + hdrwords + 1);
		qib_flush_wc();
	} else
		qib_pio_copy(piobuf + 2, hdr, hdrwords);
	qib_sendbuf_done(dd, bufn);
}
