queue_push_back(struct packet_queue *pq, struct packet *pkt)
{
    uint16_t pktnum = (pkt - pq->pkts->pdescriptor);

    if (pq->count == pq->pkts->num)
    {
        pbuf_release(pq->pkts, pkt);
        return;
    }

    pq->records[pq->head] = pktnum;

    pq->head = (pq->head + 1) % pq->pkts->num;

    ++pq->count;
}
