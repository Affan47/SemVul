scsiback_do_translation(struct vscsibk_info *info,
			struct ids_tuple *v)
{
	struct v2p_entry *entry;
	struct list_head *head = &(info->v2p_entry_lists);
	unsigned long flags;

	spin_lock_irqsave(&info->v2p_lock, flags);
	list_for_each_entry(entry, head, l) {
		if ((entry->v.chn == v->chn) &&
		    (entry->v.tgt == v->tgt) &&
		    (entry->v.lun == v->lun)) {
			kref_get(&entry->kref);
			goto out;
		}
	}
	entry = NULL;

out:
	spin_unlock_irqrestore(&info->v2p_lock, flags);
	return entry;
}
