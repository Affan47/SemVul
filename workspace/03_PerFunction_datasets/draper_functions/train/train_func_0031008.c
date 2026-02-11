cgroup_taskset_add(struct task_struct *task,
			       struct cgroup_taskset *tset)
{
	struct css_set *cset;

	lockdep_assert_held(&css_set_lock);


	if (task->flags & PF_EXITING)
		return;


	if (list_empty(&task->cg_list))
		return;

	cset = task_css_set(task);
	if (!cset->mg_src_cgrp)
		return;

	list_move_tail(&task->cg_list, &cset->mg_tasks);
	if (list_empty(&cset->mg_node))
		list_add_tail(&cset->mg_node, &tset->src_csets);
	if (list_empty(&cset->mg_dst_cset->mg_node))
		list_move_tail(&cset->mg_dst_cset->mg_node,
			       &tset->dst_csets);
}
