musb_test_mode_show(struct seq_file *s, void *unused)
{
	struct musb		*musb = s->private;
	unsigned		test;

	test = musb_readb(musb->mregs, MUSB_TESTMODE);

	if (test & MUSB_TEST_FORCE_HOST)
		seq_printf(s, "force host\n");

	if (test & MUSB_TEST_FIFO_ACCESS)
		seq_printf(s, "fifo access\n");

	if (test & MUSB_TEST_FORCE_FS)
		seq_printf(s, "force full-speed\n");

	if (test & MUSB_TEST_FORCE_HS)
		seq_printf(s, "force high-speed\n");

	if (test & MUSB_TEST_PACKET)
		seq_printf(s, "test packet\n");

	if (test & MUSB_TEST_K)
		seq_printf(s, "test K\n");

	if (test & MUSB_TEST_J)
		seq_printf(s, "test J\n");

	if (test & MUSB_TEST_SE0_NAK)
		seq_printf(s, "test SE0 NAK\n");

	return 0;
}
