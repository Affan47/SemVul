get_xendump_panic_task(void)
{
	int i;
	ulong task;
	struct task_context *tc;

	switch (xd->flags & (XC_CORE_ORIG|XC_CORE_ELF|XC_SAVE))
	{
	case XC_CORE_ORIG:
	case XC_CORE_ELF:
		if (machdep->xendump_panic_task)
			return (machdep->xendump_panic_task((void *)xd));
		break;

	case XC_SAVE:
        	for (i = 0; i < NR_CPUS; i++) {
                	if (!(task = tt->active_set[i]))
                        	continue;
			tc = task_to_context(task);
			if (is_kernel_thread(task) &&
			    STREQ(tc->comm, "suspend"))
				return tc->task;
        	}
		break;
	}

	return NO_TASK;
}
