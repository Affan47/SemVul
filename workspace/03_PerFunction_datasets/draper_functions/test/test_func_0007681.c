telem_pss_trc_verb_write(struct file *file,
					const char __user *userbuf,
					size_t count, loff_t *ppos)
{
	u32 verbosity;
	int err;

	if (kstrtou32_from_user(userbuf, count, 0, &verbosity))
		return -EFAULT;

	err = telemetry_set_trace_verbosity(TELEM_PSS, verbosity);
	if (err) {
		pr_err("Changing PSS Trace Verbosity Failed. Error %d\n", err);
		count = err;
	}

	return count;
}
