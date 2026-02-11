ntty_shutdown(struct tty_port *tport)
{
	struct port *port = container_of(tport, struct port, port);
	struct nozomi *dc = port->dc;
	unsigned long flags;

	DBG1("close: %d", port->token_dl);
	spin_lock_irqsave(&dc->spin_mutex, flags);
	dc->last_ier &= ~(port->token_dl);
	writew(dc->last_ier, dc->reg_ier);
	dc->open_ttys--;
	spin_unlock_irqrestore(&dc->spin_mutex, flags);
	printk("noz: shutdown %p\n", tport);
}
