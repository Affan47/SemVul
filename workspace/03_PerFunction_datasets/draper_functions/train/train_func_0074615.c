qat_hal_clr_reset(struct icp_qat_fw_loader_handle *handle)
{
	unsigned int ae_reset_csr;
	unsigned char ae;
	unsigned int clk_csr;
	unsigned int times = 100;
	unsigned int csr;


	ae_reset_csr = GET_GLB_CSR(handle, ICP_RESET);
	ae_reset_csr &= ~(handle->hal_handle->ae_mask << RST_CSR_AE_LSB);
	ae_reset_csr &= ~(handle->hal_handle->slice_mask << RST_CSR_QAT_LSB);
	do {
		SET_GLB_CSR(handle, ICP_RESET, ae_reset_csr);
		if (!(times--))
			goto out_err;
		csr = GET_GLB_CSR(handle, ICP_RESET);
	} while ((handle->hal_handle->ae_mask |
		 (handle->hal_handle->slice_mask << RST_CSR_QAT_LSB)) & csr);

	clk_csr = GET_GLB_CSR(handle, ICP_GLOBAL_CLK_ENABLE);
	clk_csr |= handle->hal_handle->ae_mask << 0;
	clk_csr |= handle->hal_handle->slice_mask << 20;
	SET_GLB_CSR(handle, ICP_GLOBAL_CLK_ENABLE, clk_csr);
	if (qat_hal_check_ae_alive(handle))
		goto out_err;


	for (ae = 0; ae < handle->hal_handle->ae_max_num; ae++) {
		if (!(handle->hal_handle->ae_mask & (1 << ae)))
			continue;
		qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES,
				  INIT_CTX_ENABLE_VALUE);
		qat_hal_wr_indr_csr(handle, ae, ICP_QAT_UCLO_AE_ALL_CTX,
				    CTX_STS_INDIRECT,
				    handle->hal_handle->upc_mask &
				    INIT_PC_VALUE);
		qat_hal_wr_ae_csr(handle, ae, CTX_ARB_CNTL, INIT_CTX_ARB_VALUE);
		qat_hal_wr_ae_csr(handle, ae, CC_ENABLE, INIT_CCENABLE_VALUE);
		qat_hal_put_wakeup_event(handle, ae,
					 ICP_QAT_UCLO_AE_ALL_CTX,
					 INIT_WAKEUP_EVENTS_VALUE);
		qat_hal_put_sig_event(handle, ae,
				      ICP_QAT_UCLO_AE_ALL_CTX,
				      INIT_SIG_EVENTS_VALUE);
	}
	if (qat_hal_init_esram(handle))
		goto out_err;
	if (qat_hal_wait_cycles(handle, 0, SHRAM_INIT_CYCLES, 0))
		goto out_err;
	qat_hal_reset_timestamp(handle);

	return 0;
out_err:
	pr_err("QAT: failed to get device out of reset\n");
	return -EFAULT;
}
