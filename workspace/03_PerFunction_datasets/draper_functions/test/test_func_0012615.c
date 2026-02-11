Connect()
{
	struct usb_device *pDevice = FindDevice(m_nVendorId, m_nProductId);
	if (!pDevice)
		return IB_DEVICE_NOT_FOUND;

	usb_dev_handle *pHandle = usb_open(pDevice);
	if (!pHandle)
		return IB_FAILED_TO_OPEN;

	m_pDevice = pHandle;
	if(usb_set_configuration(m_pDevice, 1) < 0)
	{
		CloseUsb();
		return IB_FAILED_TO_CONFIGURE;
	}

	if(usb_claim_interface(m_pDevice, 0) < 0)
	{
		CloseUsb();
		return IB_FAILED_TO_CLAIM;
	}

	ERR_CODE code;
	if ((code = RequestInitial(m_pSend, m_pRecv)) != IB_SUCCESS)
		return code;

	const char *ptr;
	GetResponse(ptr);

	return IB_SUCCESS;
}
