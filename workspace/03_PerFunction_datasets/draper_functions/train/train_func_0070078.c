InitEmbeddedNICMacAddressValues()
{
	uint8_t i;
	uint8_t j;
	for (i = 0; i < MAX_LOM; i++) {
		EmbeddedNICMacAddress.LOMMacAddress[i].BladSlotNumber = 0;
		EmbeddedNICMacAddress.LOMMacAddress[i].MacType = LOM_MACTYPE_RESERVED;
		EmbeddedNICMacAddress.LOMMacAddress[i].EthernetStatus =
			LOM_ETHERNET_RESERVED;
		EmbeddedNICMacAddress.LOMMacAddress[i].NICNumber = 0;
		EmbeddedNICMacAddress.LOMMacAddress[i].Reserved = 0;
		for (j = 0; j < MACADDRESSLENGH; j++) {
			EmbeddedNICMacAddress.LOMMacAddress[i].MacAddressByte[j] = 0;
			EmbeddedNICMacAddress_10G.MacAddress[i].MacAddressByte[j] = 0;
		}
	}
}
