qib_user_sdma_send_desc(struct qib_pportdata *ppd,
				struct list_head *pktlist)
{
	struct qib_devdata *dd = ppd->dd;
	u16 nfree, nsent;
	u16 tail, tail_c;
	u8 gen, gen_c;

	nfree = qib_sdma_descq_freecnt(ppd);
	if (!nfree)
		return;

retry:
	nsent = 0;
	tail_c = tail = ppd->sdma_descq_tail;
	gen_c = gen = ppd->sdma_generation;
	while (!list_empty(pktlist)) {
		struct qib_user_sdma_pkt *pkt =
			list_entry(pktlist->next, struct qib_user_sdma_pkt,
				   list);
		int i, j, c = 0;
		unsigned ofs = 0;
		u16 dtail = tail;

		for (i = pkt->index; i < pkt->naddr && nfree; i++) {
			qib_user_sdma_send_frag(ppd, pkt, i, ofs, tail, gen);
			ofs += pkt->addr[i].length >> 2;

			if (++tail == ppd->sdma_descq_cnt) {
				tail = 0;
				++gen;
				ppd->sdma_intrequest = 1;
			} else if (tail == (ppd->sdma_descq_cnt>>1)) {
				ppd->sdma_intrequest = 1;
			}
			nfree--;
			if (pkt->addr[i].last_desc == 0)
				continue;


			if (ofs > dd->piosize2kmax_dwords) {
				for (j = pkt->index; j <= i; j++) {
					ppd->sdma_descq[dtail].qw[0] |=
						cpu_to_le64(1ULL << 14);
					if (++dtail == ppd->sdma_descq_cnt)
						dtail = 0;
				}
			}
			c += i + 1 - pkt->index;
			pkt->index = i + 1;
			tail_c = dtail = tail;
			gen_c = gen;
			ofs = 0;
		}

		ppd->sdma_descq_added += c;
		nsent += c;
		if (pkt->index == pkt->naddr) {
			pkt->added = ppd->sdma_descq_added;
			pkt->pq->added = pkt->added;
			pkt->pq->num_pending--;
			spin_lock(&pkt->pq->sent_lock);
			pkt->pq->num_sending++;
			list_move_tail(&pkt->list, &pkt->pq->sent);
			spin_unlock(&pkt->pq->sent_lock);
		}
		if (!nfree || (nsent<<2) > ppd->sdma_descq_cnt)
			break;
	}


	if (ppd->sdma_descq_tail != tail_c) {
		ppd->sdma_generation = gen_c;
		dd->f_sdma_update_tail(ppd, tail_c);
	}

	if (nfree && !list_empty(pktlist))
		goto retry;
}
