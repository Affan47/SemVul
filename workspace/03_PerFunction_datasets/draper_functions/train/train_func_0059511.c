ifx_spi_tiocmset(struct tty_struct *tty,
			    unsigned int set, unsigned int clear)
{
	struct ifx_spi_device *ifx_dev = tty->driver_data;

	if (set & TIOCM_RTS)
		set_bit(IFX_SPI_RTS, &ifx_dev->signal_state);
	if (set & TIOCM_DTR)
		set_bit(IFX_SPI_DTR, &ifx_dev->signal_state);
	if (clear & TIOCM_RTS)
		clear_bit(IFX_SPI_RTS, &ifx_dev->signal_state);
	if (clear & TIOCM_DTR)
		clear_bit(IFX_SPI_DTR, &ifx_dev->signal_state);

	set_bit(IFX_SPI_UPDATE, &ifx_dev->signal_state);
	return 0;
}
