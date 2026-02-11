r3964_exit(void)
{
	int status;

	TRACE_M("cleanup_module()");

	status = tty_unregister_ldisc(N_R3964);

	if (status != 0) {
		printk(KERN_ERR "r3964: error unregistering linediscipline: "
				"%d\n", status);
	} else {
		TRACE_L("linediscipline successfully unregistered");
	}
}
