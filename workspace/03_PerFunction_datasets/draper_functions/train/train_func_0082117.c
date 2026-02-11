nicvf_rbdr_config(struct nicvf *nic, struct queue_set *qs,
			      int qidx, bool enable)
{
	struct rbdr *rbdr;
	struct rbdr_cfg rbdr_cfg;

	rbdr = &qs->rbdr[qidx];
	nicvf_reclaim_rbdr(nic, rbdr, qidx);
	if (!enable)
		return;


	nicvf_queue_reg_write(nic, NIC_QSET_RBDR_0_1_BASE,
			      qidx, (u64)(rbdr->dmem.phys_base));


	memset(&rbdr_cfg, 0, sizeof(struct rbdr_cfg));
	rbdr_cfg.ena = 1;
	rbdr_cfg.reset = 0;
	rbdr_cfg.ldwb = 0;
	rbdr_cfg.qsize = RBDR_SIZE;
	rbdr_cfg.avg_con = 0;
	rbdr_cfg.lines = rbdr->dma_size / 128;
	nicvf_queue_reg_write(nic, NIC_QSET_RBDR_0_1_CFG,
			      qidx, *(u64 *)&rbdr_cfg);


	nicvf_queue_reg_write(nic, NIC_QSET_RBDR_0_1_DOOR,
			      qidx, qs->rbdr_len - 1);


	nicvf_queue_reg_write(nic, NIC_QSET_RBDR_0_1_THRESH,
			      qidx, rbdr->thresh - 1);
}
