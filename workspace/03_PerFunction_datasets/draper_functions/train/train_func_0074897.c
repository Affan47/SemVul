sap_connect_req(void *sap_device, uint16_t maxmsgsize)
{
	DBG("sap_device %p maxmsgsize %u", sap_device, maxmsgsize);

	sap_info("connect request");

	if (simd_connect(sap_device) < 0) {
		sap_connect_rsp(sap_device, SAP_STATUS_CONNECTION_FAILED, 0);
		return;
	}

	if (send_request(u8500.io, STE_START_SAP_REQ, NULL) < 0) {
		sap_connect_rsp(sap_device, SAP_STATUS_CONNECTION_FAILED,
								SAP_BUF_SIZE);
		simd_close();
	}
}
