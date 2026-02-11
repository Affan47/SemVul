bnx2fc_send_fw_fcoe_init_msg(struct bnx2fc_hba *hba)
{
	struct fcoe_kwqe_init1 fcoe_init1;
	struct fcoe_kwqe_init2 fcoe_init2;
	struct fcoe_kwqe_init3 fcoe_init3;
	struct kwqe *kwqe_arr[3];
	int num_kwqes = 3;
	int rc = 0;

	if (!hba->cnic) {
		printk(KERN_ERR PFX "hba->cnic NULL during fcoe fw init\n");
		return -ENODEV;
	}


	memset(&fcoe_init1, 0x00, sizeof(struct fcoe_kwqe_init1));
	fcoe_init1.hdr.op_code = FCOE_KWQE_OPCODE_INIT1;
	fcoe_init1.hdr.flags = (FCOE_KWQE_LAYER_CODE <<
					FCOE_KWQE_HEADER_LAYER_CODE_SHIFT);

	fcoe_init1.num_tasks = hba->max_tasks;
	fcoe_init1.sq_num_wqes = BNX2FC_SQ_WQES_MAX;
	fcoe_init1.rq_num_wqes = BNX2FC_RQ_WQES_MAX;
	fcoe_init1.rq_buffer_log_size = BNX2FC_RQ_BUF_LOG_SZ;
	fcoe_init1.cq_num_wqes = BNX2FC_CQ_WQES_MAX;
	fcoe_init1.dummy_buffer_addr_lo = (u32) hba->dummy_buf_dma;
	fcoe_init1.dummy_buffer_addr_hi = (u32) ((u64)hba->dummy_buf_dma >> 32);
	fcoe_init1.task_list_pbl_addr_lo = (u32) hba->task_ctx_bd_dma;
	fcoe_init1.task_list_pbl_addr_hi =
				(u32) ((u64) hba->task_ctx_bd_dma >> 32);
	fcoe_init1.mtu = BNX2FC_MINI_JUMBO_MTU;

	fcoe_init1.flags = (PAGE_SHIFT <<
				FCOE_KWQE_INIT1_LOG_PAGE_SIZE_SHIFT);

	fcoe_init1.num_sessions_log = BNX2FC_NUM_MAX_SESS_LOG;


	memset(&fcoe_init2, 0x00, sizeof(struct fcoe_kwqe_init2));
	fcoe_init2.hdr.op_code = FCOE_KWQE_OPCODE_INIT2;
	fcoe_init2.hdr.flags = (FCOE_KWQE_LAYER_CODE <<
					FCOE_KWQE_HEADER_LAYER_CODE_SHIFT);

	fcoe_init2.hsi_major_version = FCOE_HSI_MAJOR_VERSION;
	fcoe_init2.hsi_minor_version = FCOE_HSI_MINOR_VERSION;


	fcoe_init2.hash_tbl_pbl_addr_lo = (u32) hba->hash_tbl_pbl_dma;
	fcoe_init2.hash_tbl_pbl_addr_hi = (u32)
					   ((u64) hba->hash_tbl_pbl_dma >> 32);

	fcoe_init2.t2_hash_tbl_addr_lo = (u32) hba->t2_hash_tbl_dma;
	fcoe_init2.t2_hash_tbl_addr_hi = (u32)
					  ((u64) hba->t2_hash_tbl_dma >> 32);

	fcoe_init2.t2_ptr_hash_tbl_addr_lo = (u32) hba->t2_hash_tbl_ptr_dma;
	fcoe_init2.t2_ptr_hash_tbl_addr_hi = (u32)
					((u64) hba->t2_hash_tbl_ptr_dma >> 32);

	fcoe_init2.free_list_count = BNX2FC_NUM_MAX_SESS;


	memset(&fcoe_init3, 0x00, sizeof(struct fcoe_kwqe_init3));
	fcoe_init3.hdr.op_code = FCOE_KWQE_OPCODE_INIT3;
	fcoe_init3.hdr.flags = (FCOE_KWQE_LAYER_CODE <<
					FCOE_KWQE_HEADER_LAYER_CODE_SHIFT);
	fcoe_init3.error_bit_map_lo = 0xffffffff;
	fcoe_init3.error_bit_map_hi = 0xffffffff;


	fcoe_init3.perf_config = 3;

	kwqe_arr[0] = (struct kwqe *) &fcoe_init1;
	kwqe_arr[1] = (struct kwqe *) &fcoe_init2;
	kwqe_arr[2] = (struct kwqe *) &fcoe_init3;

	if (hba->cnic && hba->cnic->submit_kwqes)
		rc = hba->cnic->submit_kwqes(hba->cnic, kwqe_arr, num_kwqes);

	return rc;
}
