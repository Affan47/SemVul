sdma_send_txlist(struct sdma_engine *sde,
		    struct iowait *wait,
		    struct list_head *tx_list)
{
	struct sdma_txreq *tx, *tx_next;
	int ret = 0;
	unsigned long flags;
	u16 tail = INVALID_TAIL;
	int count = 0;

	spin_lock_irqsave(&sde->tail_lock, flags);
retry:
	list_for_each_entry_safe(tx, tx_next, tx_list, list) {
		tx->wait = wait;
		if (unlikely(!__sdma_running(sde)))
			goto unlock_noconn;
		if (unlikely(tx->num_desc > sde->desc_avail))
			goto nodesc;
		if (unlikely(tx->tlen)) {
			ret = -EINVAL;
			goto update_tail;
		}
		list_del_init(&tx->list);
		tail = submit_tx(sde, tx);
		count++;
		if (tail != INVALID_TAIL &&
		    (count & SDMA_TAIL_UPDATE_THRESH) == 0) {
			sdma_update_tail(sde, tail);
			tail = INVALID_TAIL;
		}
	}
update_tail:
	if (wait)
		atomic_add(count, &wait->sdma_busy);
	if (tail != INVALID_TAIL)
		sdma_update_tail(sde, tail);
	spin_unlock_irqrestore(&sde->tail_lock, flags);
	return ret;
unlock_noconn:
	spin_lock(&sde->flushlist_lock);
	list_for_each_entry_safe(tx, tx_next, tx_list, list) {
		tx->wait = wait;
		list_del_init(&tx->list);
		if (wait)
			atomic_inc(&wait->sdma_busy);
		tx->next_descq_idx = 0;
#ifdef CONFIG_HFI1_DEBUG_SDMA_ORDER
		tx->sn = sde->tail_sn++;
		trace_hfi1_sdma_in_sn(sde, tx->sn);
#endif
		list_add_tail(&tx->list, &sde->flushlist);
		if (wait) {
			wait->tx_count++;
			wait->count += tx->num_desc;
		}
	}
	spin_unlock(&sde->flushlist_lock);
	schedule_work(&sde->flush_worker);
	ret = -ECOMM;
	goto update_tail;
nodesc:
	ret = sdma_check_progress(sde, wait, tx);
	if (ret == -EAGAIN) {
		ret = 0;
		goto retry;
	}
	sde->descq_full_count++;
	goto update_tail;
}
