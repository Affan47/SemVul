rx8025_reset_validity(struct i2c_client *client)
{
	int ctrl2 = rx8025_read_reg(client, RX8025_REG_CTRL2);

	if (ctrl2 < 0)
		return ctrl2;

	ctrl2 &= ~(RX8025_BIT_CTRL2_PON | RX8025_BIT_CTRL2_VDET);

	return rx8025_write_reg(client, RX8025_REG_CTRL2,
				ctrl2 | RX8025_BIT_CTRL2_XST);
}
