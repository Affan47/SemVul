tty_audit_buf_get(struct tty_struct *tty,
		unsigned icanon)
{
	struct tty_audit_buf *buf, *buf2;
	unsigned long flags;

	buf = NULL;
	buf2 = NULL;
	spin_lock_irqsave(&current->sighand->siglock, flags);
	if (likely(!current->signal->audit_tty))
		goto out;
	buf = current->signal->tty_audit_buf;
	if (buf) {
		atomic_inc(&buf->count);
		goto out;
	}
	spin_unlock_irqrestore(&current->sighand->siglock, flags);

	buf2 = tty_audit_buf_alloc(tty->driver->major,
				   tty->driver->minor_start + tty->index,
				   icanon);
	if (buf2 == NULL) {
		audit_log_lost("out of memory in TTY auditing");
		return NULL;
	}

	spin_lock_irqsave(&current->sighand->siglock, flags);
	if (!current->signal->audit_tty)
		goto out;
	buf = current->signal->tty_audit_buf;
	if (!buf) {
		current->signal->tty_audit_buf = buf2;
		buf = buf2;
		buf2 = NULL;
	}
	atomic_inc(&buf->count);

 out:
	spin_unlock_irqrestore(&current->sighand->siglock, flags);
	if (buf2)
		tty_audit_buf_free(buf2);
	return buf;
}
