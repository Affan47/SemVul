Handle_USBAsynchXfer (void *pdev) {
	uint16_t USB_Tx_ptr;
	uint16_t USB_Tx_length;

	if(USB_Tx_State != 1) {
		if (APP_Rx_ptr_out == APP_RX_DATA_SIZE) {
			APP_Rx_ptr_out = 0;
		}

		if(APP_Rx_ptr_out == APP_Rx_ptr_in) {
			USB_Tx_State = 0;
			return;
		}

		if(APP_Rx_ptr_out > APP_Rx_ptr_in) {
			APP_Rx_length = APP_RX_DATA_SIZE - APP_Rx_ptr_out;

		} else {
			APP_Rx_length = APP_Rx_ptr_in - APP_Rx_ptr_out;

		}
#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
		APP_Rx_length &= ~0x03;
#endif

		if (APP_Rx_length > CDC_DATA_IN_PACKET_SIZE) {
			USB_Tx_ptr = APP_Rx_ptr_out;
			USB_Tx_length = CDC_DATA_IN_PACKET_SIZE;

			APP_Rx_ptr_out += CDC_DATA_IN_PACKET_SIZE;
			APP_Rx_length -= CDC_DATA_IN_PACKET_SIZE;
		} else {
			USB_Tx_ptr = APP_Rx_ptr_out;
			USB_Tx_length = APP_Rx_length;

			APP_Rx_ptr_out += APP_Rx_length;
			APP_Rx_length = 0;
		}
		USB_Tx_State = 1;

		DCD_EP_Tx (pdev,
				   CDC_IN_EP,
				   (uint8_t*)&APP_Rx_Buffer[USB_Tx_ptr],
				   USB_Tx_length);
	}

}
