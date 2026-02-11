qat_uclo_wr_uimage_page(struct icp_qat_fw_loader_handle *handle,
				    struct icp_qat_uof_image *image)
{
	struct icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	unsigned int ctx_mask, s;
	struct icp_qat_uclo_page *page;
	unsigned char ae;
	int ctx;

	if (ICP_QAT_CTX_MODE(image->ae_mode) == ICP_QAT_UCLO_MAX_CTX)
		ctx_mask = 0xff;
	else
		ctx_mask = 0x55;


	for (ae = 0; ae < handle->hal_handle->ae_max_num; ae++) {
		if (!test_bit(ae, (unsigned long *)&image->ae_assigned))
			continue;

		for (s = 0; s < obj_handle->ae_data[ae].slice_num; s++) {
			if (image->ctx_assigned & obj_handle->ae_data[ae].
			    ae_slices[s].ctx_mask_assigned)
				break;
		}
		if (s >= obj_handle->ae_data[ae].slice_num)
			continue;
		page = obj_handle->ae_data[ae].ae_slices[s].page;
		if (!page->encap_page->def_page)
			continue;
		qat_uclo_wr_uimage_raw_page(handle, page->encap_page, ae);

		page = obj_handle->ae_data[ae].ae_slices[s].page;
		for (ctx = 0; ctx < ICP_QAT_UCLO_MAX_CTX; ctx++)
			obj_handle->ae_data[ae].ae_slices[s].cur_page[ctx] =
					(ctx_mask & (1 << ctx)) ? page : NULL;
		qat_hal_set_live_ctx(handle, (unsigned char)ae,
				     image->ctx_assigned);
		qat_hal_set_pc(handle, (unsigned char)ae, image->ctx_assigned,
			       image->entry_address);
	}
}
