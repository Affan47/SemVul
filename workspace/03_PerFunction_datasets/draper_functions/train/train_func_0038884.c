freertos_usart_write_packet_async(freertos_usart_if p_usart,
		const uint8_t *data, size_t len, portTickType block_time_ticks,
		xSemaphoreHandle notification_semaphore)
{
	status_code_t return_value;
	portBASE_TYPE usart_index;
	Usart *usart_base;

	usart_base = (Usart *) p_usart;
	usart_index = get_pdc_peripheral_details(all_usart_definitions,
			MAX_USARTS,
			(void *) usart_base);


	if (usart_index < MAX_USARTS) {
		return_value = freertos_obtain_peripheral_access_mutex(
				&(tx_dma_control[usart_index]),
				&block_time_ticks);

		if (return_value == STATUS_OK) {
			freertos_start_pdc_tx(&(tx_dma_control[usart_index]),
					data, len,
					all_usart_definitions[usart_index].pdc_base_address,
					notification_semaphore);


			usart_enable_interrupt(usart_base, US_IER_ENDTX);

			return_value = freertos_optionally_wait_transfer_completion(
					&(tx_dma_control[usart_index]),
					notification_semaphore,
					block_time_ticks);
		}
	} else {
		return_value = ERR_INVALID_ARG;
	}

	return return_value;
}
