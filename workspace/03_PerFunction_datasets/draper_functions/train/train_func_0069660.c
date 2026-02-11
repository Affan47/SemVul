sfe4003_init_phy(struct efx_nic *efx)
{
	struct falcon_board *board = falcon_board(efx);


	if (board->minor < 3 && board->major == 0)
		return;

	falcon_txc_set_gpio_dir(efx, SFE4003_RED_LED_GPIO, TXC_GPIO_DIR_OUTPUT);
	falcon_txc_set_gpio_val(efx, SFE4003_RED_LED_GPIO, SFE4003_LED_OFF);
}
