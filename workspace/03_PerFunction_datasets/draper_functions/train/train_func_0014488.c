event_dump(void)
{
	int n,i;

	printk(KERN_NOTICE "----- event dump follows -----\n");
	for (n = 0; n < EV; n++) {
		i = (ec+n) % EV;
		printk(KERN_NOTICE);
		printk(ev[i] ? ev[i] : "(null)",ev_a[i],ev_b[i]);
	}
	printk(KERN_NOTICE "----- event dump ends here -----\n");
}
