alloc_upcall(int opcode, int size)
{
	union inputArgs *inp;

	CODA_ALLOC(inp, union inputArgs *, size);
        if (!inp)
		return ERR_PTR(-ENOMEM);

        inp->ih.opcode = opcode;
	inp->ih.pid = task_pid_nr_ns(current, &init_pid_ns);
	inp->ih.pgid = task_pgrp_nr_ns(current, &init_pid_ns);
	inp->ih.uid = from_kuid(&init_user_ns, current_fsuid());

	return (void*)inp;
}
