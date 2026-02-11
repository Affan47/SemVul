serial8250_rpm_put_tx(struct uart_8250_port *p)
{
	unsigned char rpm_active;

	if (!(p->capabilities & UART_CAP_RPM))
		return;

	rpm_active = xchg(&p->rpm_tx_active, 0);
	if (!rpm_active)
		return;
	pm_runtime_mark_last_busy(p->port.dev);
	pm_runtime_put_autosuspend(p->port.dev);
}
