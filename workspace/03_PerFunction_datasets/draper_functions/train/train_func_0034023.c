hfi1_put_tid(struct hfi1_devdata *dd, u32 index,
		  u32 type, unsigned long pa, u16 order)
{
	u64 reg;
	void __iomem *base = (dd->rcvarray_wc ? dd->rcvarray_wc :
			      (dd->kregbase + RCV_ARRAY));

	if (!(dd->flags & HFI1_PRESENT))
		goto done;

	if (type == PT_INVALID) {
		pa = 0;
	} else if (type > PT_INVALID) {
		dd_dev_err(dd,
			"unexpected receive array type %u for index %u, not handled\n",
			type, index);
		goto done;
	}

	hfi1_cdbg(TID, "type %s, index 0x%x, pa 0x%lx, bsize 0x%lx",
		  pt_name(type), index, pa, (unsigned long)order);

#define RT_ADDR_SHIFT 12
	reg = RCV_ARRAY_RT_WRITE_ENABLE_SMASK
		| (u64)order << RCV_ARRAY_RT_BUF_SIZE_SHIFT
		| ((pa >> RT_ADDR_SHIFT) & RCV_ARRAY_RT_ADDR_MASK)
					<< RCV_ARRAY_RT_ADDR_SHIFT;
	writeq(reg, base + (index * 8));

	if (type == PT_EAGER)


		flush_wc();
done:
	return;
}
