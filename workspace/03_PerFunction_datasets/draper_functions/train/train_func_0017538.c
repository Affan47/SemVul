cxgbi_conn_alloc_pdu(struct iscsi_task *task, u8 opcode)
{
	struct iscsi_tcp_conn *tcp_conn = task->conn->dd_data;
	struct cxgbi_conn *cconn = tcp_conn->dd_data;
	struct cxgbi_device *cdev = cconn->chba->cdev;
	struct iscsi_conn *conn = task->conn;
	struct iscsi_tcp_task *tcp_task = task->dd_data;
	struct cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);
	struct scsi_cmnd *sc = task->sc;
	int headroom = SKB_TX_ISCSI_PDU_HEADER_MAX;

	tcp_task->dd_data = tdata;
	task->hdr = NULL;

	if (SKB_MAX_HEAD(cdev->skb_tx_rsvd) > (512 * MAX_SKB_FRAGS) &&
	    (opcode == ISCSI_OP_SCSI_DATA_OUT ||
	     (opcode == ISCSI_OP_SCSI_CMD &&
	      (scsi_bidi_cmnd(sc) || sc->sc_data_direction == DMA_TO_DEVICE))))

		headroom += min_t(unsigned int,
				SKB_MAX_HEAD(cdev->skb_tx_rsvd),
				conn->max_xmit_dlength);

	tdata->skb = alloc_skb(cdev->skb_tx_rsvd + headroom, GFP_ATOMIC);
	if (!tdata->skb) {
		struct cxgbi_sock *csk = cconn->cep->csk;
		struct net_device *ndev = cdev->ports[csk->port_id];
		ndev->stats.tx_dropped++;
		return -ENOMEM;
	}

	skb_reserve(tdata->skb, cdev->skb_tx_rsvd);
	task->hdr = (struct iscsi_hdr *)tdata->skb->data;
	task->hdr_max = SKB_TX_ISCSI_PDU_HEADER_MAX;


	if (opcode != ISCSI_OP_SCSI_DATA_OUT)
		task_reserve_itt(task, &task->hdr->itt);

	log_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
		"task 0x%p, op 0x%x, skb 0x%p,%u+%u/%u, itt 0x%x.\n",
		task, opcode, tdata->skb, cdev->skb_tx_rsvd, headroom,
		conn->max_xmit_dlength, ntohl(task->hdr->itt));

	return 0;
}
