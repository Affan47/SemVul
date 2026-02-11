show_tty_range(struct seq_file *m, struct tty_driver *p,
	dev_t from, int num)
{
	seq_printf(m, "%-20s ", p->driver_name ? p->driver_name : "unknown");
	seq_printf(m, "/dev/%-8s ", p->name);
	if (p->num > 1) {
		seq_printf(m, "%3d %d-%d ", MAJOR(from), MINOR(from),
			MINOR(from) + num - 1);
	} else {
		seq_printf(m, "%3d %7d ", MAJOR(from), MINOR(from));
	}
	switch (p->type) {
	case TTY_DRIVER_TYPE_SYSTEM:
		seq_puts(m, "system");
		if (p->subtype == SYSTEM_TYPE_TTY)
			seq_puts(m, ":/dev/tty");
		else if (p->subtype == SYSTEM_TYPE_SYSCONS)
			seq_puts(m, ":console");
		else if (p->subtype == SYSTEM_TYPE_CONSOLE)
			seq_puts(m, ":vtmaster");
		break;
	case TTY_DRIVER_TYPE_CONSOLE:
		seq_puts(m, "console");
		break;
	case TTY_DRIVER_TYPE_SERIAL:
		seq_puts(m, "serial");
		break;
	case TTY_DRIVER_TYPE_PTY:
		if (p->subtype == PTY_TYPE_MASTER)
			seq_puts(m, "pty:master");
		else if (p->subtype == PTY_TYPE_SLAVE)
			seq_puts(m, "pty:slave");
		else
			seq_puts(m, "pty");
		break;
	default:
		seq_printf(m, "type:%d.%d", p->type, p->subtype);
	}
	seq_putc(m, '\n');
}
