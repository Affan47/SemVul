pstore_console_write(struct console *con, const char *s, unsigned c)
{
	const char *e = s + c;

	while (s < e) {
		unsigned long flags;
		u64 id;

		if (c > psinfo->bufsize)
			c = psinfo->bufsize;

		if (oops_in_progress) {
			if (!spin_trylock_irqsave(&psinfo->buf_lock, flags))
				break;
		} else {
			spin_lock_irqsave(&psinfo->buf_lock, flags);
		}
		memcpy(psinfo->buf, s, c);
		psinfo->write(PSTORE_TYPE_CONSOLE, 0, &id, 0, 0, 0, c, psinfo);
		spin_unlock_irqrestore(&psinfo->buf_lock, flags);
		s += c;
		c = e - s;
	}
}
