do_unoptimize_kprobes(void)
{
	struct optimized_kprobe *op, *tmp;


	if (list_empty(&unoptimizing_list))
		return;


	get_online_cpus();
	mutex_lock(&text_mutex);
	arch_unoptimize_kprobes(&unoptimizing_list, &freeing_list);

	list_for_each_entry_safe(op, tmp, &freeing_list, list) {

		if (kprobe_disabled(&op->kp))
			arch_disarm_kprobe(&op->kp);
		if (kprobe_unused(&op->kp)) {


			hlist_del_rcu(&op->kp.hlist);
		} else
			list_del_init(&op->list);
	}
	mutex_unlock(&text_mutex);
	put_online_cpus();
}
