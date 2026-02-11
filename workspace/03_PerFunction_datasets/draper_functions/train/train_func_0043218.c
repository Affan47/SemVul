qlcnic_83xx_process_rcv_ring(struct qlcnic_host_sds_ring *sds_ring,
					int max)
{
	struct qlcnic_host_rds_ring *rds_ring;
	struct qlcnic_adapter *adapter = sds_ring->adapter;
	struct list_head *cur;
	struct status_desc *desc;
	struct qlcnic_rx_buffer *rxbuf = NULL;
	u8 ring;
	u64 sts_data[2];
	int count = 0, opcode;
	u32 consumer = sds_ring->consumer;

	while (count < max) {
		desc = &sds_ring->desc_head[consumer];
		sts_data[1] = le64_to_cpu(desc->status_desc_data[1]);
		opcode = qlcnic_83xx_opcode(sts_data[1]);
		if (!opcode)
			break;
		sts_data[0] = le64_to_cpu(desc->status_desc_data[0]);
		ring = QLCNIC_FETCH_RING_ID(sts_data[0]);

		switch (opcode) {
		case QLC_83XX_REG_DESC:
			rxbuf = qlcnic_83xx_process_rcv(adapter, sds_ring,
							ring, sts_data);
			break;
		case QLC_83XX_LRO_DESC:
			rxbuf = qlcnic_83xx_process_lro(adapter, ring,
							sts_data);
			break;
		default:
			dev_info(&adapter->pdev->dev,
				 "Unknown opcode: 0x%x\n", opcode);
			goto skip;
		}

		if (likely(rxbuf))
			list_add_tail(&rxbuf->list, &sds_ring->free_list[ring]);
		else
			adapter->stats.null_rxbuf++;
skip:
		desc = &sds_ring->desc_head[consumer];

		desc->status_desc_data[1] = 0;
		consumer = get_next_index(consumer, sds_ring->num_desc);
		count++;
	}
	for (ring = 0; ring < adapter->max_rds_rings; ring++) {
		rds_ring = &adapter->recv_ctx->rds_rings[ring];
		if (!list_empty(&sds_ring->free_list[ring])) {
			list_for_each(cur, &sds_ring->free_list[ring]) {
				rxbuf = list_entry(cur, struct qlcnic_rx_buffer,
						   list);
				qlcnic_alloc_rx_skb(adapter, rds_ring, rxbuf);
			}
			spin_lock(&rds_ring->lock);
			list_splice_tail_init(&sds_ring->free_list[ring],
					      &rds_ring->free_list);
			spin_unlock(&rds_ring->lock);
		}
		qlcnic_post_rx_buffers_nodb(adapter, rds_ring, ring);
	}
	if (count) {
		sds_ring->consumer = consumer;
		writel(consumer, sds_ring->crb_sts_consumer);
	}
	return count;
}
