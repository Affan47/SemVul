qat_hal_batch_wr_lm(struct icp_qat_fw_loader_handle *handle,
			unsigned char ae,
			struct icp_qat_uof_batch_init *lm_init_header)
{
	struct icp_qat_uof_batch_init *plm_init;
	uint64_t *micro_inst_arry;
	int micro_inst_num;
	int alloc_inst_size;
	int first_exec = 1;
	int stat = 0;

	plm_init = lm_init_header->next;
	alloc_inst_size = lm_init_header->size;
	if ((unsigned int)alloc_inst_size > handle->hal_handle->max_ustore)
		alloc_inst_size = handle->hal_handle->max_ustore;
	micro_inst_arry = kmalloc_array(alloc_inst_size, sizeof(uint64_t),
					GFP_KERNEL);
	if (!micro_inst_arry)
		return -ENOMEM;
	micro_inst_num = 0;
	while (plm_init) {
		unsigned int addr, *value, size;

		ae = plm_init->ae;
		addr = plm_init->addr;
		value = plm_init->value;
		size = plm_init->size;
		micro_inst_num += qat_hal_concat_micro_code(micro_inst_arry,
							    micro_inst_num,
							    size, addr, value);
		plm_init = plm_init->next;
	}

	if (micro_inst_arry && (micro_inst_num > 0)) {
		micro_inst_arry[micro_inst_num++] = 0x0E000010000ull;
		stat = qat_hal_exec_micro_init_lm(handle, ae, 0, &first_exec,
						  micro_inst_arry,
						  micro_inst_num);
	}
	kfree(micro_inst_arry);
	return stat;
}
