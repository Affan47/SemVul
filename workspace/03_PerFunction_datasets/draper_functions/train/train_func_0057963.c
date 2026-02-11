disarm_kprobe(struct kprobe *kp, bool reopt)
{
	if (unlikely(kprobe_ftrace(kp))) {
		disarm_kprobe_ftrace(kp);
		return;
	}

	mutex_lock(&text_mutex);
	__disarm_kprobe(kp, reopt);
	mutex_unlock(&text_mutex);
}
