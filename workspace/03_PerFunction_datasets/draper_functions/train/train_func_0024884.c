unregister_kretprobes(struct kretprobe **rps, int num)
{
	int i;

	if (num <= 0)
		return;
	mutex_lock(&kprobe_mutex);
	for (i = 0; i < num; i++)
		if (__unregister_kprobe_top(&rps[i]->kp) < 0)
			rps[i]->kp.addr = NULL;
	mutex_unlock(&kprobe_mutex);

	synchronize_sched();
	for (i = 0; i < num; i++) {
		if (rps[i]->kp.addr) {
			__unregister_kprobe_bottom(&rps[i]->kp);
			cleanup_rp_inst(rps[i]);
		}
	}
}
