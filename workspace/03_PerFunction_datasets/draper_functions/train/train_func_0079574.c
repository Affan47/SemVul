qlt_handle_abts_recv(struct scsi_qla_host *vha, response_t *pkt)
{
	struct qla_tgt_sess_op *op;

	op = kzalloc(sizeof(*op), GFP_ATOMIC);

	if (!op) {


		qlt_response_pkt_all_vps(vha, pkt);
		return;
	}

	memcpy(&op->atio, pkt, sizeof(*pkt));
	op->vha = vha;
	op->chip_reset = vha->hw->chip_reset;
	INIT_WORK(&op->work, qlt_handle_abts_recv_work);
	queue_work(qla_tgt_wq, &op->work);
	return;
}
