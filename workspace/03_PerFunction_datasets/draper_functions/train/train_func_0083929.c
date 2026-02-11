adv_get_sglist(struct asc_board *boardp, adv_req_t *reqp,
	       ADV_SCSI_REQ_Q *scsiqp, struct scsi_cmnd *scp, int use_sg)
{
	adv_sgblk_t *sgblkp, *prev_sgblkp;
	struct scatterlist *slp;
	int sg_elem_cnt;
	ADV_SG_BLOCK *sg_block, *prev_sg_block;
	dma_addr_t sgblk_paddr;
	int i;

	slp = scsi_sglist(scp);
	sg_elem_cnt = use_sg;
	prev_sgblkp = NULL;
	prev_sg_block = NULL;
	reqp->sgblkp = NULL;

	for (;;) {


		sgblkp = dma_pool_alloc(boardp->adv_sgblk_pool, GFP_ATOMIC,
					&sgblk_paddr);
		if (!sgblkp) {
			ASC_DBG(1, "no free adv_sgblk_t\n");
			ASC_STATS(scp->device->host, adv_build_nosg);


			while ((sgblkp = reqp->sgblkp) != NULL) {

				reqp->sgblkp = sgblkp->next_sgblkp;
				sgblkp->next_sgblkp = NULL;
				dma_pool_free(boardp->adv_sgblk_pool, sgblkp,
					      sgblkp->sg_addr);
			}
			return ASC_BUSY;
		}

		sgblkp->sg_addr = sgblk_paddr;
		sgblkp->next_sgblkp = NULL;
		sg_block = &sgblkp->sg_block;


		if (reqp->sgblkp == NULL) {

			reqp->sgblkp = sgblkp;


			scsiqp->sg_list_ptr = sg_block;
			scsiqp->sg_real_addr = cpu_to_le32(sgblk_paddr);
		} else {

			prev_sgblkp->next_sgblkp = sgblkp;


			prev_sg_block->sg_ptr = cpu_to_le32(sgblk_paddr);
		}

		for (i = 0; i < NO_OF_SG_PER_BLOCK; i++) {
			sg_block->sg_list[i].sg_addr =
					cpu_to_le32(sg_dma_address(slp));
			sg_block->sg_list[i].sg_count =
					cpu_to_le32(sg_dma_len(slp));
			ASC_STATS_ADD(scp->device->host, xfer_sect,
				      DIV_ROUND_UP(sg_dma_len(slp), 512));

			if (--sg_elem_cnt == 0) {


				sg_block->sg_cnt = i + 1;
				sg_block->sg_ptr = 0L;
				return ADV_SUCCESS;
			}
			slp++;
		}
		sg_block->sg_cnt = NO_OF_SG_PER_BLOCK;
		prev_sg_block = sg_block;
		prev_sgblkp = sgblkp;
	}
}
