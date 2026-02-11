adc_input_select_SB055x(struct hw *hw, enum ADCSRC type, unsigned char boost)
{
	u32 data;


	data = hw_read_20kx(hw, GPIO);
	data &= 0xec73;
	switch (type) {
	case ADC_MICIN:
		data |= (0x1<<7) | (0x1<<8) | (0x1<<9) ;
		data |= boost ? (0x1<<2) : 0;
		break;
	case ADC_LINEIN:
		data |= (0x1<<8);
		break;
	case ADC_AUX:
		data |= (0x1<<8) | (0x1<<12);
		break;
	case ADC_NONE:
		data |= (0x1<<12);
		break;
	default:
		return -1;
	}

	hw_write_20kx(hw, GPIO, data);

	return 0;
}
