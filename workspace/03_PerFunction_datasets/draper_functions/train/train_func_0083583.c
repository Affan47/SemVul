stm32_console_write(struct console *co, const char *s, unsigned cnt)
{
	struct uart_port *port = &stm32_ports[co->index].port;
	unsigned long flags;
	u32 old_cr1, new_cr1;
	int locked = 1;

	local_irq_save(flags);
	if (port->sysrq)
		locked = 0;
	else if (oops_in_progress)
		locked = spin_trylock(&port->lock);
	else
		spin_lock(&port->lock);


	old_cr1 = readl_relaxed(port->membase + USART_CR1);
	new_cr1 = old_cr1 & ~USART_CR1_IE_MASK;
	writel_relaxed(new_cr1, port->membase + USART_CR1);

	uart_console_write(port, s, cnt, stm32_console_putchar);


	writel_relaxed(old_cr1, port->membase + USART_CR1);

	if (locked)
		spin_unlock(&port->lock);
	local_irq_restore(flags);
}
