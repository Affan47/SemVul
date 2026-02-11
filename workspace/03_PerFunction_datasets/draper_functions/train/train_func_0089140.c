pack_fifo(struct isp116x *isp116x)
{
	struct isp116x_ep *ep;
	struct ptd *ptd;
	int buflen = isp116x->atl_last_dir == PTD_DIR_IN
	    ? isp116x->atl_bufshrt : isp116x->atl_buflen;

	isp116x_write_reg16(isp116x, HCuPINT, HCuPINT_AIIEOT);
	isp116x_write_reg16(isp116x, HCXFERCTR, buflen);
	isp116x_write_addr(isp116x, HCATLPORT | ISP116x_WRITE_OFFSET);
	for (ep = isp116x->atl_active; ep; ep = ep->active) {
		ptd = &ep->ptd;
		dump_ptd(ptd);
		dump_ptd_out_data(ptd, ep->data);
		isp116x_write_data16(isp116x, ptd->count);
		isp116x_write_data16(isp116x, ptd->mps);
		isp116x_write_data16(isp116x, ptd->len);
		isp116x_write_data16(isp116x, ptd->faddr);
		buflen -= sizeof(struct ptd);

		if (ep->active || (isp116x->atl_last_dir != PTD_DIR_IN)) {
			write_ptddata_to_fifo(isp116x, ep->data, ep->length);
			buflen -= ALIGN(ep->length, 4);
		}
	}
	BUG_ON(buflen);
}
