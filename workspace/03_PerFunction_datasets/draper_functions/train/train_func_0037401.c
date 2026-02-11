__mlog_printk(const u64 *mask, const char *func, int line,
		   const char *fmt, ...)
{
	struct va_format vaf;
	va_list args;
	const char *level;
	const char *prefix = "";

	if (!__mlog_test_u64(*mask, mlog_and_bits) ||
	    __mlog_test_u64(*mask, mlog_not_bits))
		return;

	if (*mask & ML_ERROR) {
		level = KERN_ERR;
		prefix = "ERROR: ";
	} else if (*mask & ML_NOTICE) {
		level = KERN_NOTICE;
	} else {
		level = KERN_INFO;
	}

	va_start(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	printk("%s(%s,%u,%u):%s:%d %s%pV",
	       level, current->comm, task_pid_nr(current),
	       raw_smp_processor_id(), func, line, prefix, &vaf);

	va_end(args);
}
