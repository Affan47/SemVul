qat_rsa_cb(struct icp_qat_fw_pke_resp *resp)
{
	struct akcipher_request *areq = (void *)(__force long)resp->opaque;
	struct qat_rsa_request *req = PTR_ALIGN(akcipher_request_ctx(areq), 64);
	struct device *dev = &GET_DEV(req->ctx->inst->accel_dev);
	int err = ICP_QAT_FW_PKE_RESP_PKE_STAT_GET(
				resp->pke_resp_hdr.comn_resp_flags);

	err = (err == ICP_QAT_FW_COMN_STATUS_FLAG_OK) ? 0 : -EINVAL;

	if (req->src_align)
		dma_free_coherent(dev, req->ctx->key_sz, req->src_align,
				  req->in.enc.m);
	else
		dma_unmap_single(dev, req->in.enc.m, req->ctx->key_sz,
				 DMA_TO_DEVICE);

	areq->dst_len = req->ctx->key_sz;
	if (req->dst_align) {
		char *ptr = req->dst_align;

		while (!(*ptr) && areq->dst_len) {
			areq->dst_len--;
			ptr++;
		}

		if (areq->dst_len != req->ctx->key_sz)
			memmove(req->dst_align, ptr, areq->dst_len);

		scatterwalk_map_and_copy(req->dst_align, areq->dst, 0,
					 areq->dst_len, 1);

		dma_free_coherent(dev, req->ctx->key_sz, req->dst_align,
				  req->out.enc.c);
	} else {
		char *ptr = sg_virt(areq->dst);

		while (!(*ptr) && areq->dst_len) {
			areq->dst_len--;
			ptr++;
		}

		if (sg_virt(areq->dst) != ptr && areq->dst_len)
			memmove(sg_virt(areq->dst), ptr, areq->dst_len);

		dma_unmap_single(dev, req->out.enc.c, req->ctx->key_sz,
				 DMA_FROM_DEVICE);
	}

	dma_unmap_single(dev, req->phy_in, sizeof(struct qat_rsa_input_params),
			 DMA_TO_DEVICE);
	dma_unmap_single(dev, req->phy_out,
			 sizeof(struct qat_rsa_output_params),
			 DMA_TO_DEVICE);

	akcipher_request_complete(areq, err);
}
