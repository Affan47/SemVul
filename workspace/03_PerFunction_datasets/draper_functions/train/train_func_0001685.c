handle_coins(void)
{
	int coins;


	coins = input_port_3_r(0) & 3;
	if (((coins ^ last_coins) & 0x01) && (coins & 0x01) == 0)
	{
		coin_state &= ~0x01;
		cpu_set_irq_line(0, 0, ASSERT_LINE);
	}
	if (((coins ^ last_coins) & 0x02) && (coins & 0x02) == 0)
	{
		coin_state &= ~0x02;
		cpu_set_irq_line(0, 0, ASSERT_LINE);
	}
	last_coins = coins;
}
