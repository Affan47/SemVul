qib_write_ureg(const struct qib_devdata *dd,
				  enum qib_ureg regno, u64 value, int ctxt)
{
	u64 __iomem *ubase;

	if (dd->userbase)
		ubase = (u64 __iomem *)
			((char __iomem *) dd->userbase +
			 dd->ureg_align * ctxt);
	else
		ubase = (u64 __iomem *)
			(dd->uregbase +
			 (char __iomem *) dd->kregbase +
			 dd->ureg_align * ctxt);

	if (dd->kregbase && (dd->flags & QIB_PRESENT))
		writeq(value, &ubase[regno]);
}
