n_hdlc_init(void)
{
	int status;


	if (maxframe < 4096)
		maxframe = 4096;
	else if (maxframe > 65535)
		maxframe = 65535;

	printk(hdlc_banner, maxframe);

	status = tty_register_ldisc(N_HDLC, &n_hdlc_ldisc);
	if (!status)
		printk(hdlc_register_ok);
	else
		printk(hdlc_register_fail, status);

	return status;

}
