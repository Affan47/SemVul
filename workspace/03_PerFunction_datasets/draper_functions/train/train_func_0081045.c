CheckGlobalIPLimits(uint32_t ip, uint16_t DEBUG_ONLY(port))
{

	uint32_t sameIPCount = 0;
	GlobalTrackingMap::const_iterator itIP = s_globalContactIPs.find(ip);
	if (itIP != s_globalContactIPs.end()) {
		sameIPCount = itIP->second;
	}
	if (sameIPCount >= MAX_CONTACTS_IP) {
		AddDebugLogLineN(logKadRouting, wxT("Ignored kad contact (IP=") + KadIPPortToString(ip, port) + wxT(") - too many contacts with the same IP (global)"));
		return false;
	}

	uint32_t sameSubnetGlobalCount = 0;
	GlobalTrackingMap::const_iterator itSubnet = s_globalContactSubnets.find(ip & 0xFFFFFF00);
	if (itSubnet != s_globalContactSubnets.end()) {
		sameSubnetGlobalCount = itSubnet->second;
	}
	if (sameSubnetGlobalCount >= MAX_CONTACTS_SUBNET && !::IsLanIP(wxUINT32_SWAP_ALWAYS(ip))) {
		AddDebugLogLineN(logKadRouting, wxT("Ignored kad contact (IP=") + KadIPPortToString(ip, port) + wxT(") - too many contacts with the same subnet (global)"));
		return false;
	}
	return true;
}
