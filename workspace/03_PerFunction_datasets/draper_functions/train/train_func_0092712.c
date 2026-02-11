mvs_find_tag(struct mvs_info *mvi, struct sas_task *task, u32 *tag)
{
	if (task->lldd_task) {
		struct mvs_slot_info *slot;
		slot = task->lldd_task;
		*tag = slot->slot_tag;
		return 1;
	}
	return 0;
}
