reset_seeprom(struct seeprom_descriptor *sd)
{
	uint8_t temp;

	temp = sd->sd_MS;
	SEEPROM_OUTB(sd, temp);
	CLOCK_PULSE(sd, sd->sd_RDY);
	SEEPROM_OUTB(sd, temp ^ sd->sd_CK);
	CLOCK_PULSE(sd, sd->sd_RDY);
	SEEPROM_OUTB(sd, temp);
	CLOCK_PULSE(sd, sd->sd_RDY);
}
