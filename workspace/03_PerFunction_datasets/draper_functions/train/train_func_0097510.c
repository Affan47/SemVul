dev_beginio (TrapContext *context)
{
	uae_u32 request = m68k_areg (regs, 1);
	uae_u8 flags = get_byte (request + 30);
	int command = get_word (request + 28);
	struct priv_devstruct *pdev = getpdevstruct (request);
	struct devstruct *dev;
	int canquick;

	put_byte (request + 8, NT_MESSAGE);
	if (!pdev) {
		put_byte (request + 31, 32);
		return get_byte (request + 31);
	}
	dev = getdevstruct (pdev->unit);
	if (!dev) {
		put_byte (request + 31, 32);
		return get_byte (request + 31);
	}
	put_byte (request + 31, 0);
	canquick = dev_canquick (dev, request);
	if (((flags & 1) && canquick) || (canquick < 0)) {
		dev_do_io (dev, request);
		if (!(flags & 1))
			uae_ReplyMsg (request);
		return get_byte (request + 31);
	} else {
		add_async_request (dev, request, ASYNC_REQUEST_TEMP, 0);
		put_byte (request + 30, get_byte (request + 30) & ~1);
		write_comm_pipe_u32 (&dev->requests, request, 1);
		return 0;
	}
}
