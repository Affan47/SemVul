usart_init_lin_slave(Usart *p_usart, uint32_t ul_baudrate,
		uint32_t ul_mck)
{

	usart_reset(p_usart);

	usart_enable_rx(p_usart);
	usart_enable_tx(p_usart);


	p_usart->US_MR = (p_usart->US_MR & ~US_MR_USART_MODE_Msk) |
			US_MR_USART_MODE_LIN_SLAVE;


	if (usart_set_async_baudrate(p_usart, ul_baudrate, ul_mck)) {
		return 1;
	}

	return 0;
}
