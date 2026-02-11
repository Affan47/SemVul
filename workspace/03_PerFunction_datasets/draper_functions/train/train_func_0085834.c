avrftdi_check_pins_mpsse(PROGRAMMER * pgm, bool output)
{
	int pin;


	struct pin_checklist_t pin_checklist[N_PINS];

	avrftdi_t* pdata = to_pdata(pgm);


	static const struct pindef_t valid_pins_SCK  = {{0x01},{0x00}} ;
	static const struct pindef_t valid_pins_MOSI = {{0x02},{0x00}} ;
	static const struct pindef_t valid_pins_MISO = {{0x04},{0x00}} ;


	int valid_mask = ((1 << pdata->pin_limit) - 1);

	valid_mask &= ~((1 << FTDI_SCK) | (1 << FTDI_MOSI) | (1 << FTDI_MISO));

	log_debug("Using valid mask mpsse: 0x%08x\n", valid_mask);
	static struct pindef_t valid_pins_others;
	valid_pins_others.mask[0] = valid_mask;
	valid_pins_others.inverse[0] = valid_mask ;


	for(pin = 0; pin < N_PINS; ++pin) {
		pin_checklist[pin].pinname = pin;
		pin_checklist[pin].mandatory = 0;
		pin_checklist[pin].valid_pins = &valid_pins_others;
	}


	pin_checklist[PIN_AVR_SCK].mandatory = 1;
	pin_checklist[PIN_AVR_SCK].valid_pins = &valid_pins_SCK;
	pin_checklist[PIN_AVR_MOSI].mandatory = 1;
	pin_checklist[PIN_AVR_MOSI].valid_pins = &valid_pins_MOSI;
	pin_checklist[PIN_AVR_MISO].mandatory = 1;
	pin_checklist[PIN_AVR_MISO].valid_pins = &valid_pins_MISO;
	pin_checklist[PIN_AVR_RESET].mandatory = 1;


	return pins_check(pgm, pin_checklist, N_PINS, output);
}
