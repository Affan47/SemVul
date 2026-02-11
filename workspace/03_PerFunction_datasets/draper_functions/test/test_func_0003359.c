pm8001_find_tag(struct sas_task *task, u32 *tag)
{
	if (task->lldd_task) {
		struct pm8001_ccb_info *ccb;
		ccb = task->lldd_task;
		*tag = ccb->ccb_tag;
		return 1;
	}
	return 0;
}
