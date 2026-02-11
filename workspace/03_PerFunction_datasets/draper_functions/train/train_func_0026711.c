mmc_packed_init(struct mmc_queue *mq, struct mmc_card *card)
{
	struct mmc_queue_req *mqrq_cur = &mq->mqrq[0];
	struct mmc_queue_req *mqrq_prev = &mq->mqrq[1];
	int ret = 0;


	mqrq_cur->packed = kzalloc(sizeof(struct mmc_packed), GFP_KERNEL);
	if (!mqrq_cur->packed) {
		pr_warn("%s: unable to allocate packed cmd for mqrq_cur\n",
			mmc_card_name(card));
		ret = -ENOMEM;
		goto out;
	}

	mqrq_prev->packed = kzalloc(sizeof(struct mmc_packed), GFP_KERNEL);
	if (!mqrq_prev->packed) {
		pr_warn("%s: unable to allocate packed cmd for mqrq_prev\n",
			mmc_card_name(card));
		kfree(mqrq_cur->packed);
		mqrq_cur->packed = NULL;
		ret = -ENOMEM;
		goto out;
	}

	INIT_LIST_HEAD(&mqrq_cur->packed->list);
	INIT_LIST_HEAD(&mqrq_prev->packed->list);

out:
	return ret;
}
