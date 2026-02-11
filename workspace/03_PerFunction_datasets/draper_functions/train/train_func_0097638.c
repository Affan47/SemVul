slcan_init(void)
{
	int status;

	if (maxdev < 4)
		maxdev = 4;

	pr_info("slcan: serial line CAN interface driver\n");
	pr_info("slcan: %d dynamic interface channels.\n", maxdev);

	slcan_devs = kzalloc(sizeof(struct net_device *)*maxdev, GFP_KERNEL);
	if (!slcan_devs)
		return -ENOMEM;


	status = tty_register_ldisc(N_SLCAN, &slc_ldisc);
	if (status)  {
		printk(KERN_ERR "slcan: can't register line discipline\n");
		kfree(slcan_devs);
	}
	return status;
}
