efx_vfdi_init_evq(struct siena_vf *vf)
{
	struct efx_nic *efx = vf->efx;
	struct vfdi_req *req = vf->buf.addr;
	unsigned vf_evq = req->u.init_evq.index;
	unsigned buf_count = req->u.init_evq.buf_count;
	unsigned abs_evq = abs_index(vf, vf_evq);
	unsigned buftbl = EFX_BUFTBL_EVQ_BASE(vf, vf_evq);
	efx_oword_t reg;

	if (bad_vf_index(efx, vf_evq) ||
	    bad_buf_count(buf_count, EFX_MAX_VF_EVQ_SIZE)) {
		if (net_ratelimit())
			netif_err(efx, hw, efx->net_dev,
				  "ERROR: Invalid INIT_EVQ from %s: evq %d bufs %d\n",
				  vf->pci_name, vf_evq, buf_count);
		return VFDI_RC_EINVAL;
	}

	efx_siena_sriov_bufs(efx, buftbl, req->u.init_evq.addr, buf_count);

	EFX_POPULATE_OWORD_3(reg,
			     FRF_CZ_TIMER_Q_EN, 1,
			     FRF_CZ_HOST_NOTIFY_MODE, 0,
			     FRF_CZ_TIMER_MODE, FFE_CZ_TIMER_MODE_DIS);
	efx_writeo_table(efx, &reg, FR_BZ_TIMER_TBL, abs_evq);
	EFX_POPULATE_OWORD_3(reg,
			     FRF_AZ_EVQ_EN, 1,
			     FRF_AZ_EVQ_SIZE, __ffs(buf_count),
			     FRF_AZ_EVQ_BUF_BASE_ID, buftbl);
	efx_writeo_table(efx, &reg, FR_BZ_EVQ_PTR_TBL, abs_evq);

	if (vf_evq == 0) {
		memcpy(vf->evq0_addrs, req->u.init_evq.addr,
		       buf_count * sizeof(u64));
		vf->evq0_count = buf_count;
	}

	return VFDI_RC_SUCCESS;
}
