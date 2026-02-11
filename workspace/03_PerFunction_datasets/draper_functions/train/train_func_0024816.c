usart_init_hw_handshaking(Usart *p_usart,
		const sam_usart_opt_t *p_usart_opt, uint32_t ul_mck)
{

	if (usart_init_rs232(p_usart, p_usart_opt, ul_mck)) {
		return 1;
	}


	p_usart->US_MR = (p_usart->US_MR & ~US_MR_USART_MODE_Msk) |
			US_MR_USART_MODE_HW_HANDSHAKING;

	return 0;
}
