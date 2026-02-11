gdi_eeprom(struct cx88_core *core, u8 *eeprom_data)
{
	const char *name = (eeprom_data[0x0d] < ARRAY_SIZE(gdi_tuner))
		? gdi_tuner[eeprom_data[0x0d]].name : NULL;

	info_printk(core, "GDI: tuner=%s\n", name ? name : "unknown");
	if (NULL == name)
		return;
	core->board.tuner_type = gdi_tuner[eeprom_data[0x0d]].id;
	core->board.radio.type = gdi_tuner[eeprom_data[0x0d]].fm ?
		CX88_RADIO : 0;
}
