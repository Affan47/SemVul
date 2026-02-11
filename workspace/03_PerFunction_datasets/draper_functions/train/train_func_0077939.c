process_qm_data(void)
{
	pkt_t p;
	pkt_t *pt;
	int ret;

	ret = read(ggg->qm->sock, ggg->qm->buf + ggg->qm->input_offset, BUF_SZ - ggg->qm->input_offset);
	if (ret == 0)
	{
		LOG("QM closed connection\n");
		close_qm();
		return;
	}
	if (ret < 0)
	{
		LOG("QM: WARNING: read() from queing manager: %s\n",
		    strerror(errno));
		LOG("QM:          closing QM connection\n");
		close_qm();
		return;
	}

	pt = (pkt_t *) ggg->qm->buf;

	int plen = ret + ggg->qm->input_offset;
	if ((plen > BUF_SZ) || (plen <= 0))
	{
		LOG("QM: input reset %d\n", plen);
		ggg->qm->input_offset = 0;
		return;
	}
	int ret_pkt;
        do {
		p.hdr = ntohl(pt->hdr);
		p.pkt_len = ntohl(pt->pkt_len);
		p.data = (uint8_t *) &(pt->data);

		if (p.pkt_len < 8)
		{
			LOG("QM: short packet tells me its %d bytes long\n", p.pkt_len);
			return;
		}

		ret_pkt = in_packet(&p, plen);

		if(ret_pkt == -1) {
			ggg->qm->input_offset += plen;
		} else {
			if( ((int)p.pkt_len <= plen) &&
			    ((int)p.pkt_len > 0)     &&
			    ((int)p.pkt_len < FIFO_WIDTH)) {

				plen -= (int)p.pkt_len;

				if ((plen > BUF_SZ) || (plen <= 0))
				{
					LOG("QM: input reset %d\n", plen);
					ggg->qm->input_offset = 0;
					return;
				}

				memmove(ggg->qm->buf, ggg->qm->buf + p.pkt_len, plen);
			}
			ggg->qm->input_offset = 0;
		}
	} while(ret_pkt == 0 && plen != 0);
}
