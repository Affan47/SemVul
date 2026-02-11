ebt_get_mac_and_mask(const char *from, unsigned char *to,
  unsigned char *mask)
{
	char *p;
	int i;
	struct ether_addr *addr;

	if (strcasecmp(from, "Unicast") == 0) {
		memcpy(to, mac_type_unicast, ETH_ALEN);
		memcpy(mask, msk_type_unicast, ETH_ALEN);
		return 0;
	}
	if (strcasecmp(from, "Multicast") == 0) {
		memcpy(to, mac_type_multicast, ETH_ALEN);
		memcpy(mask, msk_type_multicast, ETH_ALEN);
		return 0;
	}
	if (strcasecmp(from, "Broadcast") == 0) {
		memcpy(to, mac_type_broadcast, ETH_ALEN);
		memcpy(mask, msk_type_broadcast, ETH_ALEN);
		return 0;
	}
	if (strcasecmp(from, "BGA") == 0) {
		memcpy(to, mac_type_bridge_group, ETH_ALEN);
		memcpy(mask, msk_type_bridge_group, ETH_ALEN);
		return 0;
	}
	if ( (p = strrchr(from, '/')) != NULL) {
		*p = '\0';
		if (!(addr = ether_aton(p + 1)))
			return -1;
		memcpy(mask, addr, ETH_ALEN);
	} else
		memset(mask, 0xff, ETH_ALEN);
	if (!(addr = ether_aton(from)))
		return -1;
	memcpy(to, addr, ETH_ALEN);
	for (i = 0; i < ETH_ALEN; i++)
		to[i] &= mask[i];
	return 0;
}
