tomoyo_warn_oom(const char *function)
{

	static pid_t tomoyo_last_pid;
	const pid_t pid = current->pid;
	if (tomoyo_last_pid != pid) {
		printk(KERN_WARNING "ERROR: Out of memory at %s.\n",
		       function);
		tomoyo_last_pid = pid;
	}
	if (!tomoyo_policy_loaded)
		panic("MAC Initialization failed.\n");
}
