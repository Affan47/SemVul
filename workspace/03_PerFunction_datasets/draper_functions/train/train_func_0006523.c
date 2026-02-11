write_csr(const struct hfi1_devdata *dd, u32 offset, u64 value)
{
	if (dd->flags & HFI1_PRESENT)
		writeq(value, (void __iomem *)dd->kregbase + offset);
}
