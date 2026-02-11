xgene_cle_set_rss_idt(struct xgene_enet_pdata *pdata)
{
	u32 fpsel, dstqid, nfpsel, idt_reg, idx;
	int i, ret = 0;
	u16 pool_id;

	for (i = 0; i < XGENE_CLE_IDT_ENTRIES; i++) {
		idx = i % pdata->rxq_cnt;
		pool_id = pdata->rx_ring[idx]->buf_pool->id;
		fpsel = xgene_enet_ring_bufnum(pool_id) - 0x20;
		dstqid = xgene_enet_dst_ring_num(pdata->rx_ring[idx]);
		nfpsel = 0;
		idt_reg = 0;

		xgene_cle_idt_to_hw(dstqid, fpsel, nfpsel, &idt_reg);
		ret = xgene_cle_dram_wr(&pdata->cle, &idt_reg, 1, i,
					RSS_IDT, CLE_CMD_WR);
		if (ret)
			return ret;
	}

	ret = xgene_cle_set_rss_skeys(&pdata->cle);
	if (ret)
		return ret;

	return 0;
}
