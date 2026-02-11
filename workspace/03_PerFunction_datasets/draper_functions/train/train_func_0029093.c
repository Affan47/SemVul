moxa_poll_port(struct moxa_port *p, unsigned int handle,
		u16 __iomem *ip)
{
	struct tty_struct *tty = tty_port_tty_get(&p->port);
	void __iomem *ofsAddr;
	unsigned int inited = p->port.flags & ASYNC_INITIALIZED;
	u16 intr;

	if (tty) {
		if (test_bit(EMPTYWAIT, &p->statusflags) &&
				MoxaPortTxQueue(p) == 0) {
			clear_bit(EMPTYWAIT, &p->statusflags);
			tty_wakeup(tty);
		}
		if (test_bit(LOWWAIT, &p->statusflags) && !tty->stopped &&
				MoxaPortTxQueue(p) <= WAKEUP_CHARS) {
			clear_bit(LOWWAIT, &p->statusflags);
			tty_wakeup(tty);
		}

		if (inited && !test_bit(TTY_THROTTLED, &tty->flags) &&
				MoxaPortRxQueue(p) > 0) {
			MoxaPortReadData(p);
			tty_schedule_flip(&p->port);
		}
	} else {
		clear_bit(EMPTYWAIT, &p->statusflags);
		MoxaPortFlushData(p, 0);
	}

	if (!handle)
		goto put;

	intr = readw(ip);
	if (intr == 0)
		goto put;

	writew(0, ip);
	ofsAddr = p->tableAddr;
	if (intr & IntrTx)
		writew(readw(ofsAddr + HostStat) & ~WakeupTx,
				ofsAddr + HostStat);

	if (!inited)
		goto put;

	if (tty && (intr & IntrBreak) && !I_IGNBRK(tty)) {
		tty_insert_flip_char(&p->port, 0, TTY_BREAK);
		tty_schedule_flip(&p->port);
	}

	if (intr & IntrLine)
		moxa_new_dcdstate(p, readb(ofsAddr + FlagStat) & DCD_state);
put:
	tty_kref_put(tty);

	return 0;
}
