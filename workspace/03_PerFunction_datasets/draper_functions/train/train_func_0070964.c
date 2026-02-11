qib_read_6120cntrs(struct qib_devdata *dd, loff_t pos, char **namep,
			      u64 **cntrp)
{
	u32 ret;

	if (namep) {
		ret = dd->cspec->cntrnamelen;
		if (pos >= ret)
			ret = 0;
		else
			*namep = (char *)cntr6120names;
	} else {
		u64 *cntr = dd->cspec->cntrs;
		int i;

		ret = dd->cspec->ncntrs * sizeof(u64);
		if (!cntr || pos >= ret) {

			ret = 0;
			goto done;
		}
		if (pos >= ret) {
			ret = 0;
			goto done;
		}
		*cntrp = cntr;
		for (i = 0; i < dd->cspec->ncntrs; i++)
			*cntr++ = read_6120_creg32(dd, cntr6120indices[i]);
	}
done:
	return ret;
}
