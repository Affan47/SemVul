snd_seq_oss_readq_pick(struct seq_oss_readq *q, union evrec *rec)
{
	if (q->qlen == 0)
		return -EAGAIN;
	memcpy(rec, &q->q[q->head], sizeof(*rec));
	return 0;
}
