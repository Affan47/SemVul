getProductCode (char* productCode, const CmtDeviceId deviceId)
{
	CMT3LOG("L3: getProductCode %p %08x\n",productCode,deviceId);
	CMT3EXITLOG;

	DO_DATA_REQUEST(CMT_MID_REQPRODUCTCODE);

	uint16_t len = rcv.getDataSize();
	memcpy(productCode,rcv.getDataBuffer(),len);
	productCode[len] = '\0';

	return m_lastResult = XRV_OK;
}
