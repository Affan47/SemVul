pc87360_write_value(struct pc87360_data *data, u8 ldi, u8 bank,
				u8 reg, u8 value)
{
	mutex_lock(&(data->lock));
	if (bank != NO_BANK)
		outb_p(bank, data->address[ldi] + PC87365_REG_BANK);
	outb_p(value, data->address[ldi] + reg);
	mutex_unlock(&(data->lock));
}
