pio_toggle_pin(uint32_t ul_pin)
{
	Pio *p_pio = (Pio *)((uint32_t)PIOA + (PIO_DELTA * (ul_pin >> 5)));
	if (p_pio->PIO_ODSR & (1 << (ul_pin & 0x1F))) {

		p_pio->PIO_CODR = 1 << (ul_pin & 0x1F);
	} else {

		p_pio->PIO_SODR = 1 << (ul_pin & 0x1F);
	}
}
