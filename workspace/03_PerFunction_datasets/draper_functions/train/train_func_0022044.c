qla1280_req_pkt(struct scsi_qla_host *ha)
{
	struct device_reg __iomem *reg = ha->iobase;
	request_t *pkt = NULL;
	int cnt;
	uint32_t timer;

	ENTER("qla1280_req_pkt");


	for (timer = 15000000; timer; timer--) {
		if (ha->req_q_cnt > 0) {

			cnt = RD_REG_WORD(&reg->mailbox4);
			if (ha->req_ring_index < cnt)
				ha->req_q_cnt = cnt - ha->req_ring_index;
			else
				ha->req_q_cnt =
					REQUEST_ENTRY_CNT - (ha->req_ring_index - cnt);
		}


		if (ha->req_q_cnt > 0) {
			ha->req_q_cnt--;
			pkt = ha->request_ring_ptr;


			memset(pkt, 0, REQUEST_ENTRY_SIZE);


			pkt->sys_define = (uint8_t) ha->req_ring_index;


			pkt->entry_count = 1;

			break;
		}

		udelay(2);


		qla1280_poll(ha);
	}

	if (!pkt)
		dprintk(2, "qla1280_req_pkt: **** FAILED ****\n");
	else
		dprintk(3, "qla1280_req_pkt: exiting normally\n");

	return pkt;
}
