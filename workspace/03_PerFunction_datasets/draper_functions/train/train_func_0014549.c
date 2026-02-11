asd_clear_nexus(struct sas_task *task)
{
	int res = TMF_RESP_FUNC_FAILED;
	int leftover;
	struct asd_ascb *tascb = task->lldd_task;
	DECLARE_COMPLETION_ONSTACK(completion);
	unsigned long flags;

	tascb->completion = &completion;

	ASD_DPRINTK("task not done, clearing nexus\n");
	if (tascb->tag_valid)
		res = asd_clear_nexus_tag(task);
	else
		res = asd_clear_nexus_index(task);
	leftover = wait_for_completion_timeout(&completion,
					       AIC94XX_SCB_TIMEOUT);
	tascb->completion = NULL;
	ASD_DPRINTK("came back from clear nexus\n");
	spin_lock_irqsave(&task->task_state_lock, flags);
	if (leftover < 1)
		res = TMF_RESP_FUNC_FAILED;
	if (task->task_state_flags & SAS_TASK_STATE_DONE)
		res = TMF_RESP_FUNC_COMPLETE;
	spin_unlock_irqrestore(&task->task_state_lock, flags);

	return res;
}
