dev_access_u64_csr(const struct cntr_entry *entry, void *context,
			    int vl, int mode, u64 data)
{
	struct hfi1_devdata *dd = context;

	u64 val = 0;
	u64 csr = entry->csr;

	if (entry->flags & CNTR_VL) {
		if (vl == CNTR_INVALID_VL)
			return 0;
		csr += 8 * vl;
	} else {
		if (vl != CNTR_INVALID_VL)
			return 0;
	}

	val = read_write_csr(dd, csr, mode, data);
	return val;
}
