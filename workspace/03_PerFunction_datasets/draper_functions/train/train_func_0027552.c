NFQUEUE_print_v1(const void *ip,
                             const struct xt_entry_target *target, int numeric)
{
	const struct xt_NFQ_info_v1 *tinfo = (const void *)target->data;
	unsigned int last = tinfo->queues_total;

	if (last > 1) {
		last += tinfo->queuenum - 1;
		printf(" NFQUEUE balance %u:%u", tinfo->queuenum, last);
	} else {
		printf(" NFQUEUE num %u", tinfo->queuenum);
	}
}
