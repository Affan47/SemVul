snic_tgt_del_all(struct snic *snic)
{
	struct snic_tgt *tgt = NULL;
	struct list_head *cur, *nxt;
	unsigned long flags;

	mutex_lock(&snic->disc.mutex);
	spin_lock_irqsave(snic->shost->host_lock, flags);

	list_for_each_safe(cur, nxt, &snic->disc.tgt_list) {
		tgt = list_entry(cur, struct snic_tgt, list);
		tgt->state = SNIC_TGT_STAT_DEL;
		list_del_init(&tgt->list);
		SNIC_HOST_INFO(snic->shost, "Tgt %d q'ing for del\n", tgt->id);
		queue_work(snic_glob->event_q, &tgt->del_work);
		tgt = NULL;
	}
	spin_unlock_irqrestore(snic->shost->host_lock, flags);

	scsi_flush_work(snic->shost);
	mutex_unlock(&snic->disc.mutex);
}
