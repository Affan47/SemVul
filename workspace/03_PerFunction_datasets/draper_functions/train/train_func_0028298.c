dmi_processor_voltage(uint8_t code, s_dmi * dmi)
{

    static const uint16_t voltage[] = {
	5000,
	3300,
	2900
    };
    int i;

    if (code & 0x80)
	dmi->processor.voltage_mv = (code & 0x7f) * 100;
    else {
	for (i = 0; i <= 2; i++)
	    if (code & (1 << i))
		dmi->processor.voltage_mv = voltage[i];
    }
}
