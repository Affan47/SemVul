get_bssid(struct usbnet *usbdev, u8 bssid[ETH_ALEN])
{
	int ret, len;

	len = ETH_ALEN;
	ret = rndis_query_oid(usbdev, RNDIS_OID_802_11_BSSID,
			      bssid, &len);

	if (ret != 0)
		eth_zero_addr(bssid);

	return ret;
}
