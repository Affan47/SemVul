pm8001_task_done(struct sas_task *task)
{
	if (!del_timer(&task->slow_task->timer))
		return;
	complete(&task->slow_task->completion);
}
