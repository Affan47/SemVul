gtt_task_freeze (GttTask *tsk)
{
	if (!tsk ||!tsk->parent) return;
	tsk->parent->frozen = TRUE;
}
