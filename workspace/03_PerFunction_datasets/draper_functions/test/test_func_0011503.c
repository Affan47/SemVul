qlt_pci_map_calc_cnt(struct qla_tgt_prm *prm)
{
	struct qla_tgt_cmd *cmd = prm->cmd;

	BUG_ON(cmd->sg_cnt == 0);

	prm->sg = (struct scatterlist *)cmd->sg;
	prm->seg_cnt = pci_map_sg(prm->tgt->ha->pdev, cmd->sg,
	    cmd->sg_cnt, cmd->dma_data_direction);
	if (unlikely(prm->seg_cnt == 0))
		goto out_err;

	prm->cmd->sg_mapped = 1;

	if (cmd->se_cmd.prot_op == TARGET_PROT_NORMAL) {


		if (prm->seg_cnt > prm->tgt->datasegs_per_cmd)
			prm->req_cnt += DIV_ROUND_UP(prm->seg_cnt -
			prm->tgt->datasegs_per_cmd,
			prm->tgt->datasegs_per_cont);
	} else {

		if ((cmd->se_cmd.prot_op == TARGET_PROT_DIN_INSERT) ||
		    (cmd->se_cmd.prot_op == TARGET_PROT_DOUT_STRIP)) {
			prm->seg_cnt = DIV_ROUND_UP(cmd->bufflen, cmd->blk_sz);
			prm->tot_dsds = prm->seg_cnt;
		} else
			prm->tot_dsds = prm->seg_cnt;

		if (cmd->prot_sg_cnt) {
			prm->prot_sg      = cmd->prot_sg;
			prm->prot_seg_cnt = pci_map_sg(prm->tgt->ha->pdev,
				cmd->prot_sg, cmd->prot_sg_cnt,
				cmd->dma_data_direction);
			if (unlikely(prm->prot_seg_cnt == 0))
				goto out_err;

			if ((cmd->se_cmd.prot_op == TARGET_PROT_DIN_INSERT) ||
			    (cmd->se_cmd.prot_op == TARGET_PROT_DOUT_STRIP)) {

				prm->prot_seg_cnt = DIV_ROUND_UP(cmd->bufflen,
								cmd->blk_sz);
				prm->tot_dsds += prm->prot_seg_cnt;
			} else
				prm->tot_dsds += prm->prot_seg_cnt;
		}
	}

	return 0;

out_err:
	ql_dbg(ql_dbg_tgt, prm->cmd->vha, 0xe04d,
	    "qla_target(%d): PCI mapping failed: sg_cnt=%d",
	    0, prm->cmd->sg_cnt);
	return -1;
}
