usart_get_writeprotect_status(Usart *p_usart)
{
	uint32_t reg_value;

	reg_value = p_usart->US_WPSR;
	if (reg_value & US_WPSR_WPVS) {
		return (reg_value & US_WPSR_WPVSRC_Msk) >> US_WPSR_WPVSRC_Pos;
	} else {
		return 0;
	}
}
