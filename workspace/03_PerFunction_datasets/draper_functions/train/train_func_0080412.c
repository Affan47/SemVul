bGet_descriptor_patch(void)
{
	if (mDEV_REQ_VALUE_HIGH() == 1)
	{
		uint8_t *p = (uint8_t *)u8UsbDeviceDescriptor;


		ath_hal_memcpy(UsbDeviceDescriptorPatch, p,
				sizeof(UsbDeviceDescriptorPatch));


		UsbDeviceDescriptorPatch[BCD_DEVICE_OFFSET] =
			BCD_DEVICE_FW_SIGNATURE;

		pu8DescriptorEX = UsbDeviceDescriptorPatch;
		u16TxRxCounter = mTABLE_LEN(u8UsbDeviceDescriptor[0]);

		if (u16TxRxCounter > mDEV_REQ_LENGTH())
			u16TxRxCounter = mDEV_REQ_LENGTH();

		A_USB_EP0_TX_DATA();

		return TRUE;
	} else if (mDEV_REQ_VALUE_HIGH() == 2) {
		uint8_t *p = (uint8_t *)u8ConfigDescriptorEX;


		ath_hal_memcpy(ConfigDescriptorPatch, p,
				sizeof(ConfigDescriptorPatch));


		if (mDEV_REQ_VALUE_LOW() == 0) {

			pu8DescriptorEX = ConfigDescriptorPatch;
			u16TxRxCounter = ConfigDescriptorPatch[1];
		} else
			return FALSE;

		if (u16TxRxCounter > mDEV_REQ_LENGTH())
			u16TxRxCounter = mDEV_REQ_LENGTH();

		A_USB_EP0_TX_DATA();
		return TRUE;
	} else
		return bGet_descriptor();
}
