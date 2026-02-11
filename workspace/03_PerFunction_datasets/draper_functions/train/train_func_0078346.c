__subn_get_opa_cable_info(struct opa_smp *smp, u32 am, u8 *data,
				     struct ib_device *ibdev, u8 port,
				     u32 *resp_len)
{
	struct hfi1_devdata *dd = dd_from_ibdev(ibdev);
	u32 addr = OPA_AM_CI_ADDR(am);
	u32 len = OPA_AM_CI_LEN(am) + 1;
	int ret;

#define __CI_PAGE_SIZE (1 << 7)
#define __CI_PAGE_MASK ~(__CI_PAGE_SIZE - 1)
#define __CI_PAGE_NUM(a) ((a) & __CI_PAGE_MASK)


	if (addr >= 4096 ||
		(__CI_PAGE_NUM(addr) != __CI_PAGE_NUM(addr + len - 1))) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	ret = get_cable_info(dd, port, addr, len, data);

	if (ret == -ENODEV) {
		smp->status |= IB_SMP_UNSUP_METH_ATTR;
		return reply((struct ib_mad_hdr *)smp);
	}


	if (ret < 0 && ret != -ERANGE) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	if (resp_len)
		*resp_len += len;

	return reply((struct ib_mad_hdr *)smp);
}
