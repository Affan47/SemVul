qat_hal_wr_indr_csr(struct icp_qat_fw_loader_handle *handle,
				unsigned char ae, unsigned int ctx_mask,
				unsigned int ae_csr, unsigned int csr_val)
{
	unsigned int ctx, cur_ctx;

	qat_hal_rd_ae_csr(handle, ae, CSR_CTX_POINTER, &cur_ctx);

	for (ctx = 0; ctx < ICP_QAT_UCLO_MAX_CTX; ctx++) {
		if (!(ctx_mask & (1 << ctx)))
			continue;
		qat_hal_wr_ae_csr(handle, ae, CSR_CTX_POINTER, ctx);
		qat_hal_wr_ae_csr(handle, ae, ae_csr, csr_val);
	}

	qat_hal_wr_ae_csr(handle, ae, CSR_CTX_POINTER, cur_ctx);
}
