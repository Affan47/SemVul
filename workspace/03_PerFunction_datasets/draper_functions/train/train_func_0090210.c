set_lcd_level(int level)
{
	u8 buf[2];

	if (level < 0 || level >= MSI_LCD_LEVEL_MAX)
		return -EINVAL;

	buf[0] = 0x80;
	buf[1] = (u8) (level*31);

	return ec_transaction(MSI_EC_COMMAND_LCD_LEVEL, buf, sizeof(buf),
			      NULL, 0);
}
